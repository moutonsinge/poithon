/*
  test_py_c.c

  mingw32-make -f makefile.tdmgcc64
  # set some environments for python pathes before execute it
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Python.h>

int main(int ac, char **av)
{
  fprintf(stderr, "sizeof(size_t): %d\n", sizeof(size_t));
  Py_NoSiteFlag = 1;
  wchar_t *pn = Py_DecodeLocale(av[0], NULL);
  if(!pn){ fprintf(stderr, "error: cannot decode av[0]\n"); return 1; }
  Py_SetProgramName(pn);
  //Py_SetPythonHome(L"Python36");
  Py_InitializeEx(0);
  //if(!Py_IsInitialized()) Py_Initialize();
#if 0
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path = ['.', 'python36.zip', 'python36.zip/DLLs', 'python36.zip/Lib', 'python36.zip/site-packages']");
#endif
#if 0
  PyObject *fo = PyFile_FromString(av[1], "r");
  int res = PyRun_SimpleFile(PyFile_AsFile(fo), av[1]);
#endif
  PyRun_SimpleString("a=12.34567");
  PyRun_SimpleString("print(f'A, {a:20.17f}')");
  PyRun_SimpleString("print(f'あ, {a:20.17f}')");
  PyRun_SimpleString(
    "from time import time, ctime\n"
    "print('Today is', ctime(time()))");
  PyObject *so_op = PyUnicode_FromString("operator");
  PyObject *mo_op = PyImport_Import(so_op);
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('test')");
  PyObject *so_test = PyUnicode_FromString("test_py_code");
  PyObject *mo_test = PyImport_Import(so_test);
  // PyRun_SimpleString("print(test_py_code.fnc(12345679, 72))");
  PyObject *fnc = PyObject_GetAttrString(mo_test, "fnc");
  PyObject *x = PyLong_FromLong(12345679);
  PyObject *y = PyLong_FromLong(72);
  PyObject *arg = PyTuple_New(2);
  PyTuple_SetItem(arg, 0, x);
  PyTuple_SetItem(arg, 1, y);
  PyObject *r = PyObject_Call(fnc, arg, NULL);
  fprintf(stderr, "result: %ld\n", PyLong_AsLong(r));
  //if(Py_IsInitialized()) Py_Finalize();
  if(Py_FinalizeEx() < 0){ fprintf(stderr, "error: Py_FinalizeEx()\n"); return 2; }
  PyMem_RawFree(pn);
  return 0;
}

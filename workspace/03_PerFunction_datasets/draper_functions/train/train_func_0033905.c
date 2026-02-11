_wrap_plotstuff_run_commandf(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj;
  PyObject *varargs;
  PyObject *newargs;

  newargs = PyTuple_GetSlice(args,0,2);
  varargs = PyTuple_GetSlice(args,2,PyTuple_Size(args)+1);
  resultobj = _wrap_plotstuff_run_commandf__varargs__(NULL,newargs,varargs);
  Py_XDECREF(newargs);
  Py_XDECREF(varargs);
  return resultobj;
}

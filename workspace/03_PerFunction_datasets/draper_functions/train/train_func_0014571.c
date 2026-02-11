_wrap_SwigPyIterator___sub__(PyObject *self, PyObject *args) {
  int argc;
  PyObject *argv[3];
  int ii;

  if (!PyTuple_Check(args)) SWIG_fail;
  argc = args ? (int)PyObject_Length(args) : 0;
  for (ii = 0; (ii < 2) && (ii < argc); ii++) {
    argv[ii] = PyTuple_GET_ITEM(args,ii);
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_swig__SwigPyIterator, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      int res = SWIG_ConvertPtr(argv[1], 0, SWIGTYPE_p_swig__SwigPyIterator, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_SwigPyIterator___sub____SWIG_1(self, args);
      }
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_swig__SwigPyIterator, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      {
        int res = SWIG_AsVal_ptrdiff_t(argv[1], NULL);
        _v = SWIG_CheckState(res);
      }
      if (_v) {
        return _wrap_SwigPyIterator___sub____SWIG_0(self, args);
      }
    }
  }

fail:
  Py_INCREF(Py_NotImplemented);
  return Py_NotImplemented;
}

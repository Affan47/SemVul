_wrap_write(PyObject *self, PyObject *args) {
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
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_Agraph_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      void *vptr = 0;
      int res = SWIG_ConvertPtr(argv[1], &vptr, SWIGTYPE_p_FILE, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_write__SWIG_1(self, args);
      }
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_Agraph_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      int res = SWIG_AsCharPtrAndSize(argv[1], 0, NULL, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_write__SWIG_0(self, args);
      }
    }
  }

fail:
  SWIG_SetErrorMsg(PyExc_NotImplementedError,"Wrong number or type of arguments for overloaded function 'write'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    write(Agraph_t *,char const *)\n"
    "    write(Agraph_t *,FILE *)\n");
  return 0;
}

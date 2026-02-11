_wrap_new_seaudit_model_t(PyObject *self, PyObject *args) {
  int argc;
  PyObject *argv[3];
  int ii;

  if (!PyTuple_Check(args)) SWIG_fail;
  argc = args ? (int)PyObject_Length(args) : 0;
  for (ii = 0; (ii < 2) && (ii < argc); ii++) {
    argv[ii] = PyTuple_GET_ITEM(args,ii);
  }
  if ((argc >= 0) && (argc <= 2)) {
    int _v;
    if (argc <= 0) {
      return _wrap_new_seaudit_model_t__SWIG_0(self, args);
    }
    int res = SWIG_AsCharPtrAndSize(argv[0], 0, NULL, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      if (argc <= 1) {
        return _wrap_new_seaudit_model_t__SWIG_0(self, args);
      }
      void *vptr = 0;
      int res = SWIG_ConvertPtr(argv[1], &vptr, SWIGTYPE_p_seaudit_log_t, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_new_seaudit_model_t__SWIG_0(self, args);
      }
    }
  }
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_seaudit_model_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_seaudit_model_t__SWIG_1(self, args);
    }
  }
  if (argc == 1) {
    int _v;
    int res = SWIG_AsCharPtrAndSize(argv[0], 0, NULL, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_seaudit_model_t__SWIG_2(self, args);
    }
  }

fail:
  SWIG_SetErrorMsg(PyExc_NotImplementedError,"Wrong number or type of arguments for overloaded function 'new_seaudit_model_t'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    seaudit_model_t::seaudit_model_t(char *,seaudit_log_t *)\n"
    "    seaudit_model_t::seaudit_model_t(seaudit_model_t *)\n"
    "    seaudit_model_t::seaudit_model_t(char *)\n");
  return 0;
}

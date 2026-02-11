_wrap_new_apol_mls_level_t(PyObject *self, PyObject *args) {
  int argc;
  PyObject *argv[3];
  int ii;

  if (!PyTuple_Check(args)) SWIG_fail;
  argc = args ? (int)PyObject_Length(args) : 0;
  for (ii = 0; (ii < 2) && (ii < argc); ii++) {
    argv[ii] = PyTuple_GET_ITEM(args,ii);
  }
  if (argc == 0) {
    return _wrap_new_apol_mls_level_t__SWIG_0(self, args);
  }
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_apol_mls_level_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_apol_mls_level_t__SWIG_1(self, args);
    }
  }
  if (argc == 1) {
    int _v;
    int res = SWIG_AsCharPtrAndSize(argv[0], 0, NULL, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_apol_mls_level_t__SWIG_3(self, args);
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_apol_policy_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      void *vptr = 0;
      int res = SWIG_ConvertPtr(argv[1], &vptr, SWIGTYPE_p_qpol_mls_level_t, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_new_apol_mls_level_t__SWIG_4(self, args);
      }
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_apol_policy_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      void *vptr = 0;
      int res = SWIG_ConvertPtr(argv[1], &vptr, SWIGTYPE_p_qpol_level_t, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_new_apol_mls_level_t__SWIG_5(self, args);
      }
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_apol_policy_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      int res = SWIG_AsCharPtrAndSize(argv[1], 0, NULL, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_new_apol_mls_level_t__SWIG_2(self, args);
      }
    }
  }

fail:
  SWIG_SetErrorMsg(PyExc_NotImplementedError,"Wrong number or type of arguments for overloaded function 'new_apol_mls_level_t'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    apol_mls_level_t::apol_mls_level_t()\n"
    "    apol_mls_level_t::apol_mls_level_t(apol_mls_level_t *)\n"
    "    apol_mls_level_t::apol_mls_level_t(apol_policy_t *,char const *)\n"
    "    apol_mls_level_t::apol_mls_level_t(char const *)\n"
    "    apol_mls_level_t::apol_mls_level_t(apol_policy_t *,qpol_mls_level_t *)\n"
    "    apol_mls_level_t::apol_mls_level_t(apol_policy_t *,qpol_level_t *)\n");
  return 0;
}

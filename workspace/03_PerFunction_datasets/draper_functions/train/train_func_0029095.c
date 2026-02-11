_wrap_new_seaudit_model_t(ClientData clientData SWIGUNUSED, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  Tcl_Obj *CONST *argv = objv+1;
  int argc = objc-1;
  if ((argc >= 0) && (argc <= 2)) {
    int _v;
    if (argc <= 0) {
      return _wrap_new_seaudit_model_t__SWIG_0(clientData, interp, objc, argv - 1);
    }
    int res = SWIG_AsCharPtrAndSize(argv[0], 0, NULL, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      if (argc <= 1) {
        return _wrap_new_seaudit_model_t__SWIG_0(clientData, interp, objc, argv - 1);
      }
      void *vptr = 0;
      int res = SWIG_ConvertPtr(argv[1], &vptr, SWIGTYPE_p_seaudit_log_t, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_new_seaudit_model_t__SWIG_0(clientData, interp, objc, argv - 1);
      }
    }
  }
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_seaudit_model_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_seaudit_model_t__SWIG_1(clientData, interp, objc, argv - 1);
    }
  }
  if (argc == 1) {
    int _v;
    int res = SWIG_AsCharPtrAndSize(argv[0], 0, NULL, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_seaudit_model_t__SWIG_2(clientData, interp, objc, argv - 1);
    }
  }

  Tcl_SetResult(interp,(char *) "Wrong number or type of arguments for overloaded function 'new_seaudit_model_t'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    seaudit_model_t::seaudit_model_t(char *,seaudit_log_t *)\n"
    "    seaudit_model_t::seaudit_model_t(seaudit_model_t *)\n"
    "    seaudit_model_t::seaudit_model_t(char *)\n", TCL_STATIC);
  return TCL_ERROR;
}

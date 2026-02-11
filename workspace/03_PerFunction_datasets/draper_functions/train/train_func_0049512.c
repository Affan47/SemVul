_wrap_ok(ClientData clientData SWIGUNUSED, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  Tcl_Obj *CONST *argv = objv+1;
  int argc = objc-1;
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_Agraph_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_ok__SWIG_0(clientData, interp, objc, argv - 1);
    }
  }
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_Agnode_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_ok__SWIG_1(clientData, interp, objc, argv - 1);
    }
  }
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_Agedge_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_ok__SWIG_2(clientData, interp, objc, argv - 1);
    }
  }
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_Agsym_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_ok__SWIG_3(clientData, interp, objc, argv - 1);
    }
  }

  Tcl_SetResult(interp,(char *) "Wrong number or type of arguments for overloaded function 'ok'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    ok(Agraph_t *)\n"
    "    ok(Agnode_t *)\n"
    "    ok(Agedge_t *)\n"
    "    ok(Agsym_t *)\n", TCL_STATIC);
  return TCL_ERROR;
}

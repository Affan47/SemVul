_wrap_libpoldiff_get_version(ClientData clientData SWIGUNUSED, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  char *result = 0 ;

  if (SWIG_GetArgs(interp, objc, objv,":libpoldiff_get_version ") == TCL_ERROR) SWIG_fail;
  {
    char *err;
    tcl_clear_error();
    result = (char *)libpoldiff_get_version();
    if ((err = tcl_get_error()) != NULL) {
      Tcl_Obj *obj = Tcl_NewStringObj(message, -1);
      Tcl_ResetResult(interp);
      Tcl_SetObjResult(interp, obj);
      goto fail;
    }
  }
  Tcl_SetObjResult(interp,SWIG_FromCharPtr((const char *)result));
  return TCL_OK;
fail:
  return TCL_ERROR;
}

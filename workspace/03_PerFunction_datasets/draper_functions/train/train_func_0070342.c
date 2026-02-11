_wrap_new_qpol_context_t(ClientData clientData SWIGUNUSED, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  qpol_context_t *result = 0 ;

  if (SWIG_GetArgs(interp, objc, objv,":new_qpol_context_t ") == TCL_ERROR) SWIG_fail;
  {
    char *err;
    tcl_clear_error();
    result = (qpol_context_t *)new_qpol_context_t();
    if ((err = tcl_get_error()) != NULL) {
      Tcl_Obj *obj = Tcl_NewStringObj(message, -1);
      Tcl_ResetResult(interp);
      Tcl_SetObjResult(interp, obj);
      goto fail;
    }
  }
  Tcl_SetObjResult(interp, SWIG_NewInstanceObj( SWIG_as_voidptr(result), SWIGTYPE_p_qpol_context_t,0));
  return TCL_OK;
fail:
  return TCL_ERROR;
}

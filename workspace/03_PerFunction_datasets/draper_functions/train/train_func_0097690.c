ListParent(Tcl_Interp *interp, XOTclObject *obj) {
  if (obj->id) {
    Tcl_SetResult(interp, NSCmdFullName(obj->id), TCL_VOLATILE);
  }
  return TCL_OK;
}

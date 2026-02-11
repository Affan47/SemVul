XOTclONoinitMethod(ClientData cd, Tcl_Interp *interp, int objc, Tcl_Obj * CONST objv[]) {
  XOTclObject *obj = (XOTclObject*)cd;

  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (objc != 1) return XOTclObjErrArgCnt(interp, obj->cmdName, "noninit");

  obj->flags |= XOTCL_INIT_CALLED;

  return TCL_OK;
}

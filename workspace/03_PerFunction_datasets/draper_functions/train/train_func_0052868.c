XOTclCCreateMethod(ClientData cd, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  XOTclClass *cl = XOTclObjectToClass(cd);

  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (objc < 2)
    return XOTclObjErrArgCnt(interp, cl->object.cmdName, "create <obj> ?args?");

  if (RUNTIME_STATE(interp)->exitHandlerDestroyRound != XOTCL_EXITHANDLER_OFF) {
    fprintf(stderr,"### Can't create object %s during shutdown\n", ObjStr(objv[1]));
    return TCL_ERROR;
    return TCL_OK;
  }

  return createMethod(interp, cl, &cl->object, objc, objv);
}

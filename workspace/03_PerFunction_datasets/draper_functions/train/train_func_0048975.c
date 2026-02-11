callForwarder(forwardCmdClientData *tcd, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  ClientData cd;
  int result;
  XOTcl_FrameDecls;

  if (tcd->verbose) {
    Tcl_Obj *cmd = Tcl_NewListObj(objc, objv);
    fprintf(stderr,"calling %s\n", ObjStr(cmd));
    DECR_REF_COUNT(cmd);
  }
  if (tcd->objscope) {
    XOTcl_PushFrame(interp, tcd->obj);
  }
  if (tcd->objProc) {
    result = Tcl_NRCallObjProc(interp, tcd->objProc, tcd->cd, objc, objv);
  } else if (tcd->cmdName->typePtr == &XOTclObjectType
             && XOTclObjConvertObject(interp, tcd->cmdName, (void*)&cd) == TCL_OK) {

    result = XOTclObjDispatch(cd, interp, objc, objv);
  } else {

    result = Tcl_EvalObjv(interp, objc, objv, 0);
  }

  if (tcd->objscope) {
    XOTcl_PopFrame(interp, tcd->obj);
  }
  return result;
}

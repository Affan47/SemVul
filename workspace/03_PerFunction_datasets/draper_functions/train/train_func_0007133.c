XOTclCInstProcMethod(ClientData cd, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  XOTclClass *cl = XOTclObjectToClass(cd);
  char *argStr, *bdyStr, *name;
  XOTclClassOpt *opt;
  int incr = 0, result = TCL_OK;

  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (objc < 4 || objc > 7)
    return XOTclObjErrArgCnt(interp, cl->object.cmdName,
                             "instproc name ?non-positional-args? args body ?preAssertion postAssertion?");

  if (objc == 5 || objc == 7) {
    incr = 1;
  }

  argStr = ObjStr(objv[2 + incr]);
  bdyStr = ObjStr(objv[3 + incr]);
  name = ObjStr(objv[1 + incr]);

  if ((cl == RUNTIME_STATE(interp)->theObject && isDestroyString(name)) ||
      (cl == RUNTIME_STATE(interp)->theClass && isInstDestroyString(name)) ||
      (cl == RUNTIME_STATE(interp)->theClass && isAllocString(name)) ||
      (cl == RUNTIME_STATE(interp)->theClass && isCreateString(name)))
    return XOTclVarErrMsg(interp, className(cl), " instproc: '", name, "' of ",
                          className(cl), " can not be overwritten. Derive a ",
                          "sub-class", (char *) NULL);

  if (*argStr == 0 && *bdyStr == 0) {
    int rc;
    opt = cl->opt;
    if (opt && opt->assertions)
      AssertionRemoveProc(opt->assertions, name);
    rc = NSDeleteCmd(interp, cl->nsPtr, name);
    if (rc < 0)
      return XOTclVarErrMsg(interp, className(cl), " cannot delete instproc: '", name,
                            "' of class ", className(cl), (char *) NULL);
  } else {
    XOTclAssertionStore *aStore = NULL;
    if (objc > 5) {
      opt = XOTclRequireClassOpt(cl);
      if (!opt->assertions)
        opt->assertions = AssertionCreateStore();
      aStore = opt->assertions;
    }
    result = MakeProc(cl->nsPtr, aStore, &(cl->nonposArgsTable),
                      interp, objc, (Tcl_Obj **) objv, &cl->object);
  }


  FilterInvalidateObjOrders(interp, cl);

  return result;
}

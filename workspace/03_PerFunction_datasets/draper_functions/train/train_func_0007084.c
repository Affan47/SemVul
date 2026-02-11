FilterAdd(Tcl_Interp *interp, XOTclCmdList **filterList, Tcl_Obj *name,
          XOTclObject *startingObj, XOTclClass *startingCl) {
  Tcl_Command cmd;
  int ocName; Tcl_Obj **ovName;
  Tcl_Obj *guard = NULL;
  XOTclCmdList *new;
  XOTclClass *cl;

  if (Tcl_ListObjGetElements(interp, name, &ocName, &ovName) == TCL_OK && ocName > 1) {
    if (ocName == 3 && !strcmp(ObjStr(ovName[1]), XOTclGlobalStrings[XOTE_GUARD_OPTION])) {
      name = ovName[0];
      guard = ovName[2];
    }
  }

  if (!(cmd = FilterSearch(interp, ObjStr(name), startingObj, startingCl, &cl))) {
    if (startingObj)
      return XOTclVarErrMsg(interp, "filter: can't find filterproc on: ",
                            ObjStr(startingObj->cmdName), " - proc: ",
                            ObjStr(name), (char *) NULL);
    else
      return XOTclVarErrMsg(interp, "instfilter: can't find filterproc on: ",
                            ObjStr(startingCl->object.cmdName), " - proc: ",
                            ObjStr(name), (char *) NULL);
  }


  new = CmdListAdd(filterList, cmd, cl,  1);

  if (guard) {
    GuardAdd(interp, new, guard);
  } else {
    if (new->clientData)
      GuardDel(new);
  }

  return TCL_OK;
}

ListChildren(Tcl_Interp *interp, XOTclObject *obj, char *pattern, int classesOnly) {
  XOTclObject *childobj;
  Tcl_HashTable *cmdTable;
  XOTcl_FrameDecls;

  if (!obj->nsPtr) return TCL_OK;

  cmdTable = Tcl_Namespace_cmdTable(obj->nsPtr);
  if (pattern && noMetaChars(pattern)) {
    XOTcl_PushFrame(interp, obj);
    if ((childobj = XOTclpGetObject(interp, pattern)) &&
        (!classesOnly || XOTclObjectIsClass(childobj)) &&
        (childobj->id && Tcl_Command_nsPtr(childobj->id) == obj->nsPtr)
        ) {
      Tcl_SetObjResult(interp, childobj->cmdName);
    } else {
      Tcl_SetObjResult(interp, XOTclGlobalObjects[XOTE_EMPTY]);
    }
    XOTcl_PopFrame(interp, obj);
  } else {
    Tcl_Obj *list = Tcl_NewListObj(0, NULL);
    Tcl_HashSearch hSrch;
    Tcl_HashEntry *hPtr = Tcl_FirstHashEntry(cmdTable, &hSrch);
    char *key;
    XOTcl_PushFrame(interp, obj);
    for (; hPtr; hPtr = Tcl_NextHashEntry(&hSrch)) {
      key = Tcl_GetHashKey(cmdTable, hPtr);
      if (!pattern || Tcl_StringMatch(key, pattern)) {
        if ((childobj = XOTclpGetObject(interp, key)) &&
            (!classesOnly || XOTclObjectIsClass(childobj)) &&
            (childobj->id && Tcl_Command_nsPtr(childobj->id) == obj->nsPtr)
            ) {
          Tcl_ListObjAppendElement(interp, list, childobj->cmdName);
        }
      }
    }
    XOTcl_PopFrame(interp, obj);
    Tcl_SetObjResult(interp, list);
  }
  return TCL_OK;
}

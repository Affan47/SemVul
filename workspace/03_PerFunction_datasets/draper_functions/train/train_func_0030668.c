XOTclInstVar(XOTcl_Object *obji, Tcl_Interp *interp, char *name, char *destName) {
  XOTclObject *obj = (XOTclObject*) obji;
  int result;
  Tcl_Obj *alias = NULL;
  ALLOC_ON_STACK(Tcl_Obj*, 2, objv);

  objv[0] = XOTclGlobalObjects[XOTE_INSTVAR];
  objv[1] = Tcl_NewStringObj(name, -1);
  INCR_REF_COUNT(objv[1]);

  if (destName) {
    alias = Tcl_NewStringObj(destName, -1);
    INCR_REF_COUNT(alias);
    Tcl_ListObjAppendElement(interp, objv[1], alias);
  }

  result = XOTclOInstVarMethod((ClientData) obj, interp, 2, objv);

  if (destName) {
    DECR_REF_COUNT(alias);
  }
  DECR_REF_COUNT(objv[1]);
  FREE_ON_STACK(Tcl_Obj *, objv);
  return result;
}

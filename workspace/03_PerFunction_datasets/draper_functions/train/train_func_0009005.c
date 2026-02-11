XOTclRemovePMethod(Tcl_Interp *interp, XOTcl_Object *obji, char *nm) {
  XOTclObject *obj = (XOTclObject*) obji;
  if (obj->nsPtr)
    NSDeleteCmd(interp, obj->nsPtr, nm);
}

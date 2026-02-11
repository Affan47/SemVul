FindCalledClass(Tcl_Interp *interp, XOTclObject *obj) {
  XOTclCallStackContent *csc = CallStackGetTopFrame(interp);
  char *methodName;
  Tcl_Command cmd;

  if (csc->frameType == XOTCL_CSC_TYPE_PLAIN)
    return GetSelfClass(interp);

  if (csc->frameType == XOTCL_CSC_TYPE_ACTIVE_FILTER)
    methodName = ObjStr(csc->filterStackEntry->calledProc);
  else if (csc->frameType == XOTCL_CSC_TYPE_ACTIVE_MIXIN && obj->mixinStack)
    methodName = (char *) GetSelfProc(interp);
  else
    methodName = "";

  if (obj->nsPtr) {
    cmd = FindMethod(methodName, obj->nsPtr);
    if (cmd) {
      return NULL;
    }
  }

  return SearchCMethod(obj->cl, methodName, &cmd);
}

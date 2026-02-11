AssertionList(Tcl_Interp *interp, XOTclTclObjList *alist) {
  Tcl_Obj *newAssStr = Tcl_NewStringObj("", 0);
  for (; alist; alist = alist->next) {
    Tcl_AppendStringsToObj(newAssStr, "{", ObjStr(alist->content),
                           "}", (char *) NULL);
    if (alist->next)
      Tcl_AppendStringsToObj(newAssStr, " ", (char *) NULL);
  }
  return newAssStr;
}

ListProcDefault(Tcl_Interp *interp, Tcl_HashTable *table,
                char *name, char *arg, Tcl_Obj *var) {
  Tcl_Obj *defVal;
  int result;
  if (GetProcDefault(interp, table, name, arg, &defVal) == TCL_OK) {
    result = SetProcDefault(interp, var, defVal);
  } else {
    XOTclVarErrMsg(interp, "method '", name,
                   "' doesn't exist or doesn't have an argument '",
                   arg, "'", (char *) NULL);
    result = TCL_ERROR;
  }
  return result;
}

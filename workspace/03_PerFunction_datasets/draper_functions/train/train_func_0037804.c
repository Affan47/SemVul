XOTcl_DeleteCommandFromToken(Tcl_Interp *interp, Tcl_Command cmd) {
  XOTclCallStack *cs = &RUNTIME_STATE(interp)->cs;
  XOTclCallStackContent *csc = cs->top;

  for (; csc > cs->content; csc--) {
    if (csc->cmdPtr == cmd) {
      csc->cmdPtr = NULL;
    }
  }
  return Tcl_DeleteCommandFromToken(interp, cmd);
}

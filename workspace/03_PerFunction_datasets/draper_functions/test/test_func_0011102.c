callingNameSpace(Tcl_Interp *interp) {
  Tcl_Namespace *ns = NULL;
  XOTclCallStack *cs = &RUNTIME_STATE(interp)->cs;
  XOTclCallStackContent *top = cs->top;
  XOTclCallStackContent *csc = XOTclCallStackFindLastInvocation(interp, 0);


  if (csc && csc->currentFramePtr) {

    XOTclCallStackContent *called = csc<top? csc+1 : NULL;
    Tcl_CallFrame *f = called ?
      Tcl_CallFrame_callerPtr(called->currentFramePtr) : NULL;

    if (f) {
      ns = f->nsPtr;
    } else {
      Tcl_CallFrame *f = Tcl_CallFrame_callerPtr(csc->currentFramePtr);
      ns = Tcl_GetCurrentNamespace(interp);

      while (ns == RUNTIME_STATE(interp)->XOTclNS) {
        if (f) {
          ns = f->nsPtr;
          f = Tcl_CallFrame_callerPtr(f);
        } else {
          ns = Tcl_GetGlobalNamespace(interp);
        }
      }

    }
  }
  if (!ns) {

    XOTclCallStackContent *bot = cs->content + 1;

    if (top - bot >= 0 && bot->currentFramePtr) {

      Tcl_CallFrame *f = Tcl_CallFrame_callerPtr(bot->currentFramePtr);
      if (f) {
        ns = f->nsPtr;


      } else {

        ns = Tcl_GetGlobalNamespace(interp);
      }
    }
  }


  return ns;
}

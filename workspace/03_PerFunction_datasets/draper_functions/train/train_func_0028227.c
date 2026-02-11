CallStackPop(Tcl_Interp *interp) {
  XOTclCallStack *cs = &RUNTIME_STATE(interp)->cs;
  XOTclCallStackContent *csc;
  XOTclCallStackContent *h = cs->top;

  assert(cs->top > cs->content);
  csc = cs->top;


  if (csc->destroyedCmd) {
    int destroy = 1;
    TclCleanupCommand((Command *)csc->destroyedCmd);
    MEM_COUNT_FREE("command refCount", csc->destroyedCmd);


    while (--h > cs->content) {
      if (h->self == csc->self) {
        destroy = 0;
        break;
      }
    }
    if (destroy) {
      CallStackDoDestroy(interp, csc->self);
    }
  }

  cs->top--;
  MEM_COUNT_FREE("CallStack", NULL);
}

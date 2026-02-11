CallStackRestoreSavedFrames(Tcl_Interp *interp, callFrameContext *ctx) {
  if (ctx->framesSaved) {
    Tcl_Interp_varFramePtr(interp) = (CallFrame *)ctx->varFramePtr;


  }
}

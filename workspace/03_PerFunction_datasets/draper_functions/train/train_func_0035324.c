emitOptimizationRemarkAnalysis(LLVMContext &Ctx,
                                          const char *PassName,
                                          const Function &Fn,
                                          const DebugLoc &DLoc,
                                          const Twine &Msg) {
  Ctx.diagnose(
      DiagnosticInfoOptimizationRemarkAnalysis(PassName, Fn, DLoc, Msg));
}

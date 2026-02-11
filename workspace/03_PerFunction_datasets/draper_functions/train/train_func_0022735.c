EmitFunctionEntryLabel() {
  if (AFI->isThumbFunction()) {
    OutStreamer->EmitAssemblerFlag(MCAF_Code16);
    OutStreamer->EmitThumbFunc(CurrentFnSym);
  }

  OutStreamer->EmitLabel(CurrentFnSym);
}

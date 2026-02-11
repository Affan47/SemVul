Warning(SMLoc L, const Twine &Msg, ArrayRef<SMRange> Ranges) {
  if (FatalAssemblerWarnings)
    return Error(L, Msg, Ranges);
  PrintMessage(L, SourceMgr::DK_Warning, Msg, Ranges);
  PrintMacroInstantiations();
  return false;
}

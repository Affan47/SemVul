createMCStreamer(const Target &T, StringRef TT,
                                    MCContext &Ctx, MCAsmBackend &MAB,
                                    raw_ostream &OS,
                                    MCCodeEmitter *Emitter,
                                    bool RelaxAll,
                                    bool NoExecStack) {
  Triple TheTriple(TT);

  if (TheTriple.isOSDarwin())
    return createMachOStreamer(Ctx, MAB, OS, Emitter, RelaxAll);

  if (TheTriple.isOSWindows()) {
    llvm_unreachable("ARM does not support Windows COFF format");
    return NULL;
  }

  return createELFStreamer(Ctx, MAB, OS, Emitter, RelaxAll, NoExecStack);
}

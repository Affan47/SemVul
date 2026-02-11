createMCStreamer(const Target &T, StringRef TT,
                                    MCContext &Ctx, MCAsmBackend &MAB,
                                    raw_ostream &OS,
                                    MCCodeEmitter *Emitter,
                                    bool RelaxAll,
                                    bool NoExecStack) {
  if (Triple(TT).isOSDarwin())
    return createMachOStreamer(Ctx, MAB, OS, Emitter, RelaxAll);

  return createELFStreamer(Ctx, MAB, OS, Emitter, RelaxAll, NoExecStack);
}

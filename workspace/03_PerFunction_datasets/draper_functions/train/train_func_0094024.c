createBPFMCCodeEmitter(const MCInstrInfo &MCII,
                                            const MCRegisterInfo &MRI,
                                            MCContext &Ctx) {
  return new BPFMCCodeEmitter(MRI, true);
}

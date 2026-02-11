createMSP430MCInstPrinter(const Target &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCSubtargetInfo &STI) {
  if (SyntaxVariant == 0)
    return new MSP430InstPrinter(MAI);
  return 0;
}

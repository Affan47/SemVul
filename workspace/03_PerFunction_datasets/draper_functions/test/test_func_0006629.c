createMCAsmTargetStreamer(MCStreamer &S,
                                                   formatted_raw_ostream &OS,
                                                   MCInstPrinter *InstPrint,
                                                   bool IsVerboseAsm) {
  return new HexagonTargetAsmStreamer(S,  OS, IsVerboseAsm, *InstPrint);
}

PerformDAGCombine(SDNode *N,
                                               DAGCombinerInfo &DCI) const {
  CodeGenOpt::Level OptLevel = getTargetMachine().getOptLevel();
  switch (N->getOpcode()) {
    default: break;
    case ISD::ADD:
    case ISD::FADD:
      return PerformADDCombine(N, DCI, STI, OptLevel);
    case ISD::MUL:
      return PerformMULCombine(N, DCI, OptLevel);
    case ISD::SHL:
      return PerformSHLCombine(N, DCI, OptLevel);
    case ISD::AND:
      return PerformANDCombine(N, DCI);
    case ISD::SELECT:
      return PerformSELECTCombine(N, DCI);
  }
  return SDValue();
}

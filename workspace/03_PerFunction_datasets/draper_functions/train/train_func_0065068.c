ReplaceNodeResults(SDNode *N,
                                             SmallVectorImpl<SDValue>&Results,
                                             SelectionDAG &DAG) const {
  switch (N->getOpcode()) {
  default:
    llvm_unreachable("Don't know how to custom expand this!");
    return;
  case ISD::ADD:
  case ISD::SUB:
    Results.push_back(ExpandADDSUB(N, DAG));
    return;
  }
}

Select_INLINEASM(SDNode *N) {
  std::vector<SDValue> Ops(N->op_begin(), N->op_end());
  SelectInlineAsmMemoryOperands(Ops);

  std::vector<EVT> VTs;
  VTs.push_back(MVT::Other);
  VTs.push_back(MVT::Flag);
  SDValue New = CurDAG->getNode(ISD::INLINEASM, N->getDebugLoc(),
                                VTs, &Ops[0], Ops.size());
  New->setNodeId(-1);
  return New.getNode();
}

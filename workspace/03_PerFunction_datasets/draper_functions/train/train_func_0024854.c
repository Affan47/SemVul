LowerCTPOP(SDValue Op, SelectionDAG &DAG) const {
  SDLoc dl(Op);
  SDValue InpVal = Op.getOperand(0);
  if (isa<ConstantSDNode>(InpVal)) {
    uint64_t V = cast<ConstantSDNode>(InpVal)->getZExtValue();
    return DAG.getTargetConstant(countPopulation(V), dl, MVT::i64);
  }
  SDValue PopOut = DAG.getNode(HexagonISD::POPCOUNT, dl, MVT::i32, InpVal);
  return DAG.getNode(ISD::ZERO_EXTEND, dl, MVT::i64, PopOut);
}

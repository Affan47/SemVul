SelectIntrinsicWOChain(SDNode *N) {
  unsigned IID = cast<ConstantSDNode>(N->getOperand(0))->getZExtValue();
  unsigned Bits;
  switch (IID) {
  case Intrinsic::hexagon_S2_vsplatrb:
    Bits = 8;
    break;
  case Intrinsic::hexagon_S2_vsplatrh:
    Bits = 16;
    break;
  default:
    return SelectCode(N);
  }

  SDValue const &V = N->getOperand(1);
  SDValue U;
  if (isValueExtension(V, Bits, U)) {
    SDValue R = CurDAG->getNode(N->getOpcode(), SDLoc(N), N->getValueType(0),
      N->getOperand(0), U);
    return SelectCode(R.getNode());
  }
  return SelectCode(N);
}

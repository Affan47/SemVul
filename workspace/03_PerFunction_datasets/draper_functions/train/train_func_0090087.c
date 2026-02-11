SelectADDRrr(SDValue Addr, SDValue &R1, SDValue &R2) {
  if (Addr.getOpcode() == ISD::FrameIndex) return false;
  if (Addr.getOpcode() == ISD::TargetExternalSymbol ||
      Addr.getOpcode() == ISD::TargetGlobalAddress)
    return false;

  if (Addr.getOpcode() == ISD::ADD) {
    if (ConstantSDNode *CN = dyn_cast<ConstantSDNode>(Addr.getOperand(1)))
      if (isInt<13>(CN->getSExtValue()))
        return false;
    if (Addr.getOperand(0).getOpcode() == SPISD::Lo ||
        Addr.getOperand(1).getOpcode() == SPISD::Lo)
      return false;
    R1 = Addr.getOperand(0);
    R2 = Addr.getOperand(1);
    return true;
  }

  R1 = Addr;
  R2 = CurDAG->getRegister(SP::G0, MVT::i32);
  return true;
}

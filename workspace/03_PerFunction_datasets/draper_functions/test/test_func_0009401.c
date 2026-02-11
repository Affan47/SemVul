PromoteIntRes_XMULO(SDNode *N, unsigned ResNo) {

  if (ResNo == 1)
    return PromoteIntRes_Overflow(N);

  SDValue LHS = N->getOperand(0), RHS = N->getOperand(1);
  DebugLoc DL = N->getDebugLoc();
  EVT SmallVT = LHS.getValueType();


  if (N->getOpcode() == ISD::SMULO) {
    LHS = SExtPromotedInteger(LHS);
    RHS = SExtPromotedInteger(RHS);
  } else {
    LHS = ZExtPromotedInteger(LHS);
    RHS = ZExtPromotedInteger(RHS);
  }
  SDValue Mul = DAG.getNode(ISD::MUL, DL, LHS.getValueType(), LHS, RHS);


  SDValue Overflow;
  if (N->getOpcode() == ISD::UMULO) {

    SDValue Hi = DAG.getNode(ISD::SRL, DL, Mul.getValueType(), Mul,
                             DAG.getIntPtrConstant(SmallVT.getSizeInBits()));
    Overflow = DAG.getSetCC(DL, N->getValueType(1), Hi,
                            DAG.getConstant(0, Hi.getValueType()), ISD::SETNE);
  } else {

    SDValue SExt = DAG.getNode(ISD::SIGN_EXTEND_INREG, DL, Mul.getValueType(),
                               Mul, DAG.getValueType(SmallVT));
    Overflow = DAG.getSetCC(DL, N->getValueType(1), SExt, Mul, ISD::SETNE);
  }


  ReplaceValueWith(SDValue(N, 1), Overflow);
  return Mul;
}

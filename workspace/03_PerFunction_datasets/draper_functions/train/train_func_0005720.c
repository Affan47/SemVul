LowerBR_CC(SDValue Op, SelectionDAG &DAG,
                          const SparcTargetLowering &TLI,
                          bool hasHardQuad) {
  SDValue Chain = Op.getOperand(0);
  ISD::CondCode CC = cast<CondCodeSDNode>(Op.getOperand(1))->get();
  SDValue LHS = Op.getOperand(2);
  SDValue RHS = Op.getOperand(3);
  SDValue Dest = Op.getOperand(4);
  SDLoc dl(Op);
  unsigned Opc, SPCC = ~0U;


  LookThroughSetCC(LHS, RHS, CC, SPCC);


  SDValue CompareFlag;
  if (LHS.getValueType().isInteger()) {
    CompareFlag = DAG.getNode(SPISD::CMPICC, dl, MVT::Glue, LHS, RHS);
    if (SPCC == ~0U) SPCC = IntCondCCodeToICC(CC);

    Opc = LHS.getValueType() == MVT::i32 ? SPISD::BRICC : SPISD::BRXCC;
  } else {
    if (!hasHardQuad && LHS.getValueType() == MVT::f128) {
      if (SPCC == ~0U) SPCC = FPCondCCodeToFCC(CC);
      CompareFlag = TLI.LowerF128Compare(LHS, RHS, SPCC, dl, DAG);
      Opc = SPISD::BRICC;
    } else {
      CompareFlag = DAG.getNode(SPISD::CMPFCC, dl, MVT::Glue, LHS, RHS);
      if (SPCC == ~0U) SPCC = FPCondCCodeToFCC(CC);
      Opc = SPISD::BRFCC;
    }
  }
  return DAG.getNode(Opc, dl, MVT::Other, Chain, Dest,
                     DAG.getConstant(SPCC, dl, MVT::i32), CompareFlag);
}

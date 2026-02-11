lowerMSABitClearImm(SDValue Op, SelectionDAG &DAG) {
  SDLoc DL(Op);
  EVT ResTy = Op->getValueType(0);
  APInt BitImm = APInt(ResTy.getVectorElementType().getSizeInBits(), 1)
                 << cast<ConstantSDNode>(Op->getOperand(2))->getAPIntValue();
  SDValue BitMask = DAG.getConstant(~BitImm, DL, ResTy);

  return DAG.getNode(ISD::AND, DL, ResTy, Op->getOperand(1), BitMask);
}

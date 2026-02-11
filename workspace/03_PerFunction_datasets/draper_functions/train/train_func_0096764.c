visitFABS(SDNode *N) {
  SDValue N0 = N->getOperand(0);
  ConstantFPSDNode *N0CFP = dyn_cast<ConstantFPSDNode>(N0);
  EVT VT = N->getValueType(0);


  if (N0CFP && VT != MVT::ppcf128)
    return DAG.getNode(ISD::FABS, N->getDebugLoc(), VT, N0);

  if (N0.getOpcode() == ISD::FABS)
    return N->getOperand(0);


  if (N0.getOpcode() == ISD::FNEG || N0.getOpcode() == ISD::FCOPYSIGN)
    return DAG.getNode(ISD::FABS, N->getDebugLoc(), VT, N0.getOperand(0));


  if (N0.getOpcode() == ISD::BIT_CONVERT && N0.getNode()->hasOneUse() &&
      N0.getOperand(0).getValueType().isInteger() &&
      !N0.getOperand(0).getValueType().isVector()) {
    SDValue Int = N0.getOperand(0);
    EVT IntVT = Int.getValueType();
    if (IntVT.isInteger() && !IntVT.isVector()) {
      Int = DAG.getNode(ISD::AND, N0.getDebugLoc(), IntVT, Int,
             DAG.getConstant(~APInt::getSignBit(IntVT.getSizeInBits()), IntVT));
      AddToWorkList(Int.getNode());
      return DAG.getNode(ISD::BIT_CONVERT, N->getDebugLoc(),
                         N->getValueType(0), Int);
    }
  }

  return SDValue();
}

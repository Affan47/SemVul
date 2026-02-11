visitFP_TO_SINT(SDNode *N) {
  SDValue N0 = N->getOperand(0);
  ConstantFPSDNode *N0CFP = dyn_cast<ConstantFPSDNode>(N0);
  EVT VT = N->getValueType(0);


  if (N0CFP)
    return DAG.getNode(ISD::FP_TO_SINT, N->getDebugLoc(), VT, N0);

  return SDValue();
}

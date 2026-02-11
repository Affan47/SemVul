PromoteFloatRes_ConstantFP(SDNode *N) {
  ConstantFPSDNode *CFPNode = cast<ConstantFPSDNode>(N);
  EVT VT = N->getValueType(0);
  SDLoc DL(N);


  EVT IVT = EVT::getIntegerVT(*DAG.getContext(), VT.getSizeInBits());
  SDValue C = DAG.getConstant(CFPNode->getValueAPF().bitcastToAPInt(), DL,
                              IVT);


  EVT NVT = TLI.getTypeToTransformTo(*DAG.getContext(), VT);
  return DAG.getNode(GetPromotionOpcode(VT, NVT), DL, NVT, C);
}

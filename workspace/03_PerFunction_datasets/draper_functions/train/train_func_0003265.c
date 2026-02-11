performOrCombine(SDNode *N,
                                           DAGCombinerInfo &DCI) const {
  SelectionDAG &DAG = DCI.DAG;
  SDValue LHS = N->getOperand(0);
  SDValue RHS = N->getOperand(1);


  if (LHS.getOpcode() == AMDGPUISD::FP_CLASS &&
      RHS.getOpcode() == AMDGPUISD::FP_CLASS) {
    SDValue Src = LHS.getOperand(0);
    if (Src != RHS.getOperand(0))
      return SDValue();

    const ConstantSDNode *CLHS = dyn_cast<ConstantSDNode>(LHS.getOperand(1));
    const ConstantSDNode *CRHS = dyn_cast<ConstantSDNode>(RHS.getOperand(1));
    if (!CLHS || !CRHS)
      return SDValue();


    static const uint32_t MaxMask = 0x3ff;

    uint32_t NewMask = (CLHS->getZExtValue() | CRHS->getZExtValue()) & MaxMask;
    SDLoc DL(N);
    return DAG.getNode(AMDGPUISD::FP_CLASS, DL, MVT::i1,
                       Src, DAG.getConstant(NewMask, DL, MVT::i32));
  }

  return SDValue();
}

WidenVecOp_CONCAT_VECTORS(SDNode *N) {


  EVT VT = N->getValueType(0);
  EVT EltVT = VT.getVectorElementType();
  SDLoc dl(N);
  unsigned NumElts = VT.getVectorNumElements();
  SmallVector<SDValue, 16> Ops(NumElts);

  EVT InVT = N->getOperand(0).getValueType();
  unsigned NumInElts = InVT.getVectorNumElements();

  unsigned Idx = 0;
  unsigned NumOperands = N->getNumOperands();
  for (unsigned i=0; i < NumOperands; ++i) {
    SDValue InOp = N->getOperand(i);
    if (getTypeAction(InOp.getValueType()) == TargetLowering::TypeWidenVector)
      InOp = GetWidenedVector(InOp);
    for (unsigned j=0; j < NumInElts; ++j)
      Ops[Idx++] = DAG.getNode(
          ISD::EXTRACT_VECTOR_ELT, dl, EltVT, InOp,
          DAG.getConstant(j, dl, TLI.getVectorIdxTy(DAG.getDataLayout())));
  }
  return DAG.getNode(ISD::BUILD_VECTOR, dl, VT, Ops);
}

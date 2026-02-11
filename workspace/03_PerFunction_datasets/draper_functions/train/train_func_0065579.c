ExpandSEXTINREG(SDValue Op) {
  EVT VT = Op.getValueType();


  if (TLI.getOperationAction(ISD::SRA, VT) == TargetLowering::Expand ||
      TLI.getOperationAction(ISD::SHL, VT) == TargetLowering::Expand)
    return DAG.UnrollVectorOp(Op.getNode());

  SDLoc DL(Op);
  EVT OrigTy = cast<VTSDNode>(Op->getOperand(1))->getVT();

  unsigned BW = VT.getScalarType().getSizeInBits();
  unsigned OrigBW = OrigTy.getScalarType().getSizeInBits();
  SDValue ShiftSz = DAG.getConstant(BW - OrigBW, DL, VT);

  Op = Op.getOperand(0);
  Op =   DAG.getNode(ISD::SHL, DL, VT, Op, ShiftSz);
  return DAG.getNode(ISD::SRA, DL, VT, Op, ShiftSz);
}

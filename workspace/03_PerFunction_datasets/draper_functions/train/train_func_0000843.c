visitSREM(SDNode *N) {
  SDValue N0 = N->getOperand(0);
  SDValue N1 = N->getOperand(1);
  ConstantSDNode *N0C = dyn_cast<ConstantSDNode>(N0);
  ConstantSDNode *N1C = dyn_cast<ConstantSDNode>(N1);
  EVT VT = N->getValueType(0);


  if (N0C && N1C && !N1C->isNullValue())
    return DAG.FoldConstantArithmetic(ISD::SREM, VT, N0C, N1C);


  if (!VT.isVector()) {
    if (DAG.SignBitIsZero(N1) && DAG.SignBitIsZero(N0))
      return DAG.getNode(ISD::UREM, N->getDebugLoc(), VT, N0, N1);
  }


  if (N1C && !N1C->isNullValue()) {
    SDValue Div = DAG.getNode(ISD::SDIV, N->getDebugLoc(), VT, N0, N1);
    AddToWorkList(Div.getNode());
    SDValue OptimizedDiv = combine(Div.getNode());
    if (OptimizedDiv.getNode() && OptimizedDiv.getNode() != Div.getNode()) {
      SDValue Mul = DAG.getNode(ISD::MUL, N->getDebugLoc(), VT,
                                OptimizedDiv, N1);
      SDValue Sub = DAG.getNode(ISD::SUB, N->getDebugLoc(), VT, N0, Mul);
      AddToWorkList(Mul.getNode());
      return Sub;
    }
  }


  if (N0.getOpcode() == ISD::UNDEF)
    return DAG.getConstant(0, VT);

  if (N1.getOpcode() == ISD::UNDEF)
    return N1;

  return SDValue();
}

LowerEXTRACT_SUBVECTOR(SDValue Op,
                                                     SelectionDAG &DAG) const {

  SmallVector<SDValue, 8> Args;
  unsigned Start = cast<ConstantSDNode>(Op.getOperand(1))->getZExtValue();
  EVT VT = Op.getValueType();
  DAG.ExtractVectorElements(Op.getOperand(0), Args, Start,
                            VT.getVectorNumElements());

  return DAG.getNode(ISD::BUILD_VECTOR, SDLoc(Op), Op.getValueType(), Args);
}

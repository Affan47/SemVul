ExpandLoad(SDValue Op) {
  DebugLoc dl = Op.getDebugLoc();
  LoadSDNode *LD = cast<LoadSDNode>(Op.getNode());
  SDValue Chain = LD->getChain();
  SDValue BasePTR = LD->getBasePtr();
  EVT SrcVT = LD->getMemoryVT();
  ISD::LoadExtType ExtType = LD->getExtensionType();

  SmallVector<SDValue, 8> LoadVals;
  SmallVector<SDValue, 8> LoadChains;
  unsigned NumElem = SrcVT.getVectorNumElements();
  unsigned Stride = SrcVT.getScalarType().getSizeInBits()/8;

  for (unsigned Idx=0; Idx<NumElem; Idx++) {
    SDValue ScalarLoad = DAG.getExtLoad(ExtType, dl,
              Op.getNode()->getValueType(0).getScalarType(),
              Chain, BasePTR, LD->getPointerInfo().getWithOffset(Idx * Stride),
              SrcVT.getScalarType(),
              LD->isVolatile(), LD->isNonTemporal(),
              LD->getAlignment());

    BasePTR = DAG.getNode(ISD::ADD, dl, BasePTR.getValueType(), BasePTR,
                       DAG.getIntPtrConstant(Stride));

     LoadVals.push_back(ScalarLoad.getValue(0));
     LoadChains.push_back(ScalarLoad.getValue(1));
  }

  SDValue NewChain = DAG.getNode(ISD::TokenFactor, dl, MVT::Other,
            &LoadChains[0], LoadChains.size());
  SDValue Value = DAG.getNode(ISD::BUILD_VECTOR, dl,
            Op.getNode()->getValueType(0), &LoadVals[0], LoadVals.size());

  AddLegalizedOperand(Op.getValue(0), Value);
  AddLegalizedOperand(Op.getValue(1), NewChain);

  return (Op.getResNo() ? NewChain : Value);
}

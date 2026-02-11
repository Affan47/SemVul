WidenVecRes_MLOAD(MaskedLoadSDNode *N) {

  EVT WidenVT = TLI.getTypeToTransformTo(*DAG.getContext(),N->getValueType(0));
  SDValue Mask = N->getMask();
  EVT MaskVT = Mask.getValueType();
  SDValue Src0 = GetWidenedVector(N->getSrc0());
  ISD::LoadExtType ExtType = N->getExtensionType();
  SDLoc dl(N);

  if (getTypeAction(MaskVT) == TargetLowering::TypeWidenVector)
    Mask = GetWidenedVector(Mask);
  else {
    EVT BoolVT = getSetCCResultType(WidenVT);


    unsigned WidenNumElts = BoolVT.getVectorNumElements();
    unsigned MaskNumElts = MaskVT.getVectorNumElements();

    unsigned NumConcat = WidenNumElts / MaskNumElts;
    SmallVector<SDValue, 16> Ops(NumConcat);
    SDValue ZeroVal = DAG.getConstant(0, dl, MaskVT);
    Ops[0] = Mask;
    for (unsigned i = 1; i != NumConcat; ++i)
      Ops[i] = ZeroVal;

    Mask = DAG.getNode(ISD::CONCAT_VECTORS, dl, BoolVT, Ops);
  }

  SDValue Res = DAG.getMaskedLoad(WidenVT, dl, N->getChain(), N->getBasePtr(),
                                  Mask, Src0, N->getMemoryVT(),
                                  N->getMemOperand(), ExtType);


  ReplaceValueWith(SDValue(N, 1), Res.getValue(1));
  return Res;
}

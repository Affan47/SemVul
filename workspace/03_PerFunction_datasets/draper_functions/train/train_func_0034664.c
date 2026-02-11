WidenVecRes_Convert(SDNode *N) {
  SDValue InOp = N->getOperand(0);
  DebugLoc dl = N->getDebugLoc();

  EVT WidenVT = TLI.getTypeToTransformTo(*DAG.getContext(), N->getValueType(0));
  unsigned WidenNumElts = WidenVT.getVectorNumElements();

  EVT InVT = InOp.getValueType();
  EVT InEltVT = InVT.getVectorElementType();
  EVT InWidenVT = EVT::getVectorVT(*DAG.getContext(), InEltVT, WidenNumElts);

  unsigned Opcode = N->getOpcode();
  unsigned InVTNumElts = InVT.getVectorNumElements();

  if (getTypeAction(InVT) == WidenVector) {
    InOp = GetWidenedVector(N->getOperand(0));
    InVT = InOp.getValueType();
    InVTNumElts = InVT.getVectorNumElements();
    if (InVTNumElts == WidenNumElts)
      return DAG.getNode(Opcode, dl, WidenVT, InOp);
  }

  if (TLI.isTypeSynthesizable(InWidenVT)) {


    if (WidenNumElts % InVTNumElts == 0) {

      unsigned NumConcat = WidenNumElts/InVTNumElts;
      SmallVector<SDValue, 16> Ops(NumConcat);
      Ops[0] = InOp;
      SDValue UndefVal = DAG.getUNDEF(InVT);
      for (unsigned i = 1; i != NumConcat; ++i)
        Ops[i] = UndefVal;
      return DAG.getNode(Opcode, dl, WidenVT,
                         DAG.getNode(ISD::CONCAT_VECTORS, dl, InWidenVT,
                         &Ops[0], NumConcat));
    }

    if (InVTNumElts % WidenNumElts == 0) {

      return DAG.getNode(Opcode, dl, WidenVT,
                         DAG.getNode(ISD::EXTRACT_SUBVECTOR, dl, InWidenVT,
                                     InOp, DAG.getIntPtrConstant(0)));
    }
  }


  SmallVector<SDValue, 16> Ops(WidenNumElts);
  EVT EltVT = WidenVT.getVectorElementType();
  unsigned MinElts = std::min(InVTNumElts, WidenNumElts);
  unsigned i;
  for (i=0; i < MinElts; ++i)
    Ops[i] = DAG.getNode(Opcode, dl, EltVT,
                         DAG.getNode(ISD::EXTRACT_VECTOR_ELT, dl, InEltVT, InOp,
                                     DAG.getIntPtrConstant(i)));

  SDValue UndefVal = DAG.getUNDEF(EltVT);
  for (; i < WidenNumElts; ++i)
    Ops[i] = UndefVal;

  return DAG.getNode(ISD::BUILD_VECTOR, dl, WidenVT, &Ops[0], WidenNumElts);
}

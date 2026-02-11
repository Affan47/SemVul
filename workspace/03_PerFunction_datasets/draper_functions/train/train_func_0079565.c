getVectorTypeBreakdownMVT(MVT VT, MVT &IntermediateVT,
                                          unsigned &NumIntermediates,
                                          EVT &RegisterVT,
                                          TargetLowering *TLI) {

  unsigned NumElts = VT.getVectorNumElements();
  MVT EltTy = VT.getVectorElementType();

  unsigned NumVectorRegs = 1;


  if (!isPowerOf2_32(NumElts)) {
    NumVectorRegs = NumElts;
    NumElts = 1;
  }


  while (NumElts > 1 && !TLI->isTypeLegal(MVT::getVectorVT(EltTy, NumElts))) {
    NumElts >>= 1;
    NumVectorRegs <<= 1;
  }

  NumIntermediates = NumVectorRegs;

  MVT NewVT = MVT::getVectorVT(EltTy, NumElts);
  if (!TLI->isTypeLegal(NewVT))
    NewVT = EltTy;
  IntermediateVT = NewVT;

  EVT DestVT = TLI->getRegisterType(NewVT);
  RegisterVT = DestVT;
  if (EVT(DestVT).bitsLT(NewVT))
    return NumVectorRegs*(NewVT.getSizeInBits()/DestVT.getSizeInBits());


  return NumVectorRegs;
}

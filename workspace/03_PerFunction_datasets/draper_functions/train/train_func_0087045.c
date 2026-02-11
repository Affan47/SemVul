SoftenFloatRes_FABS(SDNode *N) {
  EVT NVT = TLI.getTypeToTransformTo(*DAG.getContext(), N->getValueType(0));
  unsigned Size = NVT.getSizeInBits();


  APInt API = APInt::getAllOnesValue(Size);
  API.clearBit(Size - 1);
  SDValue Mask = DAG.getConstant(API, SDLoc(N), NVT);
  SDValue Op = GetSoftenedFloat(N->getOperand(0));
  return DAG.getNode(ISD::AND, SDLoc(N), NVT, Op, Mask);
}

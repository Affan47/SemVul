ExpandRes_VAARG(SDNode *N, SDValue &Lo, SDValue &Hi) {
  EVT OVT = N->getValueType(0);
  EVT NVT = TLI.getTypeToTransformTo(*DAG.getContext(), OVT);
  SDValue Chain = N->getOperand(0);
  SDValue Ptr = N->getOperand(1);
  DebugLoc dl = N->getDebugLoc();
  const unsigned Align = N->getConstantOperandVal(3);

  Lo = DAG.getVAArg(NVT, dl, Chain, Ptr, N->getOperand(2), Align);
  Hi = DAG.getVAArg(NVT, dl, Lo.getValue(1), Ptr, N->getOperand(2), 0);


  if (TLI.isBigEndian())
    std::swap(Lo, Hi);


  ReplaceValueWith(SDValue(N, 1), Hi.getValue(1));
}

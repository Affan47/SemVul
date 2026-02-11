LowerGlobalAddress(SDValue Op,
                                              SelectionDAG &DAG) const {
  EVT PtrVT = Op.getValueType();
  GlobalAddressSDNode *GSDN = cast<GlobalAddressSDNode>(Op);
  DebugLoc DL = GSDN->getDebugLoc();
  const GlobalValue *GV = GSDN->getGlobal();


  if (PPCSubTarget.isSVR4ABI() && PPCSubTarget.isPPC64()) {
    SDValue GA = DAG.getTargetGlobalAddress(GV, DL, PtrVT, GSDN->getOffset());
    return DAG.getNode(PPCISD::TOC_ENTRY, DL, MVT::i64, GA,
                       DAG.getRegister(PPC::X2, MVT::i64));
  }

  unsigned MOHiFlag, MOLoFlag;
  bool isPIC = GetLabelAccessInfo(DAG.getTarget(), MOHiFlag, MOLoFlag, GV);

  SDValue GAHi =
    DAG.getTargetGlobalAddress(GV, DL, PtrVT, GSDN->getOffset(), MOHiFlag);
  SDValue GALo =
    DAG.getTargetGlobalAddress(GV, DL, PtrVT, GSDN->getOffset(), MOLoFlag);

  SDValue Ptr = LowerLabelRef(GAHi, GALo, isPIC, DAG);


  if (MOHiFlag & PPCII::MO_NLP_FLAG)
    Ptr = DAG.getLoad(PtrVT, DL, DAG.getEntryNode(), Ptr, MachinePointerInfo(),
                      false, false, 0);
  return Ptr;
}

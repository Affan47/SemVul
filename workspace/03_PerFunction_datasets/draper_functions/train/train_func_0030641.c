SplitVecOp_MSCATTER(MaskedScatterSDNode *N,
                                              unsigned OpNo) {
  SDValue Ch  = N->getChain();
  SDValue Ptr = N->getBasePtr();
  SDValue Mask = N->getMask();
  SDValue Index = N->getIndex();
  SDValue Data = N->getValue();
  EVT MemoryVT = N->getMemoryVT();
  unsigned Alignment = N->getOriginalAlignment();
  SDLoc DL(N);

  EVT LoMemVT, HiMemVT;
  std::tie(LoMemVT, HiMemVT) = DAG.GetSplitDestVTs(MemoryVT);

  SDValue DataLo, DataHi;
  GetSplitVector(Data, DataLo, DataHi);
  SDValue MaskLo, MaskHi;
  GetSplitVector(Mask, MaskLo, MaskHi);

    SDValue PtrLo, PtrHi;
  if (Ptr.getValueType().isVector())
    std::tie(PtrLo, PtrHi) = DAG.SplitVector(Ptr, DL);
  else
    PtrLo = PtrHi = Ptr;

  SDValue IndexHi, IndexLo;
  if (Index.getNode())
    std::tie(IndexLo, IndexHi) = DAG.SplitVector(Index, DL);
  else
    IndexLo = IndexHi = Index;

  SDValue Lo, Hi;
  MachineMemOperand *MMO = DAG.getMachineFunction().
    getMachineMemOperand(N->getPointerInfo(),
                         MachineMemOperand::MOStore, LoMemVT.getStoreSize(),
                         Alignment, N->getAAInfo(), N->getRanges());

  SDValue OpsLo[] = {Ch, DataLo, MaskLo, PtrLo, IndexLo};
  Lo = DAG.getMaskedScatter(DAG.getVTList(MVT::Other), DataLo.getValueType(),
                            DL, OpsLo, MMO);

  MMO = DAG.getMachineFunction().
    getMachineMemOperand(N->getPointerInfo(),
                         MachineMemOperand::MOStore,  HiMemVT.getStoreSize(),
                         Alignment, N->getAAInfo(), N->getRanges());

  SDValue OpsHi[] = {Ch, DataHi, MaskHi, PtrHi, IndexHi};
  Hi = DAG.getMaskedScatter(DAG.getVTList(MVT::Other), DataHi.getValueType(),
                            DL, OpsHi, MMO);


  return DAG.getNode(ISD::TokenFactor, DL, MVT::Other, Lo, Hi);
}

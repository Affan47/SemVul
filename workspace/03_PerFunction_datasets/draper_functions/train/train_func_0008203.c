LowerParameter(SelectionDAG &DAG, EVT VT, EVT MemVT,
                                         SDLoc SL, SDValue Chain,
                                         unsigned Offset, bool Signed) const {
  const DataLayout &DL = DAG.getDataLayout();
  MachineFunction &MF = DAG.getMachineFunction();
  const SIRegisterInfo *TRI =
      static_cast<const SIRegisterInfo*>(Subtarget->getRegisterInfo());
  unsigned InputPtrReg = TRI->getPreloadedValue(MF, SIRegisterInfo::INPUT_PTR);

  Type *Ty = VT.getTypeForEVT(*DAG.getContext());

  MachineRegisterInfo &MRI = DAG.getMachineFunction().getRegInfo();
  MVT PtrVT = getPointerTy(DL, AMDGPUAS::CONSTANT_ADDRESS);
  PointerType *PtrTy = PointerType::get(Ty, AMDGPUAS::CONSTANT_ADDRESS);
  SDValue BasePtr = DAG.getCopyFromReg(Chain, SL,
                                       MRI.getLiveInVirtReg(InputPtrReg), PtrVT);
  SDValue Ptr = DAG.getNode(ISD::ADD, SL, PtrVT, BasePtr,
                            DAG.getConstant(Offset, SL, PtrVT));
  SDValue PtrOffset = DAG.getUNDEF(PtrVT);
  MachinePointerInfo PtrInfo(UndefValue::get(PtrTy));

  unsigned Align = DL.getABITypeAlignment(Ty);

  ISD::LoadExtType ExtTy = Signed ? ISD::SEXTLOAD : ISD::ZEXTLOAD;
  if (MemVT.isFloatingPoint())
    ExtTy = ISD::EXTLOAD;

  return DAG.getLoad(ISD::UNINDEXED, ExtTy,
                     VT, SL, Chain, Ptr, PtrOffset, PtrInfo, MemVT,
                     false,
                     true,
                     true,
                     Align);
}

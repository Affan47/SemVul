writeVarArgRegs(std::vector<SDValue> &OutChains,
                                         SDValue Chain, SDLoc DL,
                                         SelectionDAG &DAG,
                                         CCState &State) const {
  ArrayRef<MCPhysReg> ArgRegs = ABI.GetVarArgRegs();
  unsigned Idx = State.getFirstUnallocated(ArgRegs);
  unsigned RegSizeInBytes = Subtarget.getGPRSizeInBytes();
  MVT RegTy = MVT::getIntegerVT(RegSizeInBytes * 8);
  const TargetRegisterClass *RC = getRegClassFor(RegTy);
  MachineFunction &MF = DAG.getMachineFunction();
  MachineFrameInfo *MFI = MF.getFrameInfo();
  MipsFunctionInfo *MipsFI = MF.getInfo<MipsFunctionInfo>();


  int VaArgOffset;

  if (ArgRegs.size() == Idx)
    VaArgOffset =
        RoundUpToAlignment(State.getNextStackOffset(), RegSizeInBytes);
  else {
    VaArgOffset =
        (int)ABI.GetCalleeAllocdArgSizeInBytes(State.getCallingConv()) -
        (int)(RegSizeInBytes * (ArgRegs.size() - Idx));
  }


  int FI = MFI->CreateFixedObject(RegSizeInBytes, VaArgOffset, true);
  MipsFI->setVarArgsFrameIndex(FI);


  for (unsigned I = Idx; I < ArgRegs.size();
       ++I, VaArgOffset += RegSizeInBytes) {
    unsigned Reg = addLiveIn(MF, ArgRegs[I], RC);
    SDValue ArgValue = DAG.getCopyFromReg(Chain, DL, Reg, RegTy);
    FI = MFI->CreateFixedObject(RegSizeInBytes, VaArgOffset, true);
    SDValue PtrOff = DAG.getFrameIndex(FI, getPointerTy(DAG.getDataLayout()));
    SDValue Store = DAG.getStore(Chain, DL, ArgValue, PtrOff,
                                 MachinePointerInfo(), false, false, 0);
    cast<StoreSDNode>(Store.getNode())->getMemOperand()->setValue(
        (Value *)nullptr);
    OutChains.push_back(Store);
  }
}

getMips16SPRefReg(SDNode *Parent, SDValue &AliasReg) {
  auto PtrVT = getTargetLowering()->getPointerTy(CurDAG->getDataLayout());
  SDValue AliasFPReg = CurDAG->getRegister(Mips::S0, PtrVT);
  if (Parent) {
    switch (Parent->getOpcode()) {
      case ISD::LOAD: {
        LoadSDNode *SD = dyn_cast<LoadSDNode>(Parent);
        switch (SD->getMemoryVT().getSizeInBits()) {
        case 8:
        case 16:
          AliasReg = Subtarget->getFrameLowering()->hasFP(*MF)
                         ? AliasFPReg
                         : getMips16SPAliasReg();
          return;
        }
        break;
      }
      case ISD::STORE: {
        StoreSDNode *SD = dyn_cast<StoreSDNode>(Parent);
        switch (SD->getMemoryVT().getSizeInBits()) {
        case 8:
        case 16:
          AliasReg = Subtarget->getFrameLowering()->hasFP(*MF)
                         ? AliasFPReg
                         : getMips16SPAliasReg();
          return;
        }
        break;
      }
    }
  }
  AliasReg = CurDAG->getRegister(Mips::SP, PtrVT);
  return;

}

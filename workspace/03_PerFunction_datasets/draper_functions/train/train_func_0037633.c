loadRegFromStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                     unsigned DestReg, int FI,
                     const TargetRegisterClass *RC,
                     const TargetRegisterInfo *TRI) const {
  if (RC == ARM::GPRRegisterClass   || RC == ARM::tGPRRegisterClass ||
      RC == ARM::tcGPRRegisterClass || RC == ARM::rGPRRegisterClass ||
      RC == ARM::GPRnopcRegisterClass) {
    DebugLoc DL;
    if (I != MBB.end()) DL = I->getDebugLoc();

    MachineFunction &MF = *MBB.getParent();
    MachineFrameInfo &MFI = *MF.getFrameInfo();
    MachineMemOperand *MMO =
      MF.getMachineMemOperand(
                      MachinePointerInfo(PseudoSourceValue::getFixedStack(FI)),
                              MachineMemOperand::MOLoad,
                              MFI.getObjectSize(FI),
                              MFI.getObjectAlignment(FI));
    AddDefaultPred(BuildMI(MBB, I, DL, get(ARM::t2LDRi12), DestReg)
                   .addFrameIndex(FI).addImm(0).addMemOperand(MMO));
    return;
  }

  ARMBaseInstrInfo::loadRegFromStackSlot(MBB, I, DestReg, FI, RC, TRI);
}

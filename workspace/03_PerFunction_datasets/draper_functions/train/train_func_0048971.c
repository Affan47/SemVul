loadRegFromStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                     unsigned DestReg, int FI,
                     const TargetRegisterClass *RC,
                     const TargetRegisterInfo *TRI) const {
  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = *MF.getFrameInfo();
  MachineMemOperand *MMO = MF.getMachineMemOperand(
      MachinePointerInfo::getFixedStack(MF, FI), MachineMemOperand::MOLoad,
      MFI.getObjectSize(FI), MFI.getObjectAlignment(FI));
  DebugLoc DL;
  if (I != MBB.end()) DL = I->getDebugLoc();

  if (RC == &ARM::GPRRegClass   || RC == &ARM::tGPRRegClass ||
      RC == &ARM::tcGPRRegClass || RC == &ARM::rGPRRegClass ||
      RC == &ARM::GPRnopcRegClass) {
    AddDefaultPred(BuildMI(MBB, I, DL, get(ARM::t2LDRi12), DestReg)
                   .addFrameIndex(FI).addImm(0).addMemOperand(MMO));
    return;
  }

  if (ARM::GPRPairRegClass.hasSubClassEq(RC)) {


    MachineRegisterInfo *MRI = &MF.getRegInfo();
    MRI->constrainRegClass(DestReg, &ARM::GPRPair_with_gsub_1_in_rGPRRegClass);

    MachineInstrBuilder MIB = BuildMI(MBB, I, DL, get(ARM::t2LDRDi8));
    AddDReg(MIB, DestReg, ARM::gsub_0, RegState::DefineNoRead, TRI);
    AddDReg(MIB, DestReg, ARM::gsub_1, RegState::DefineNoRead, TRI);
    MIB.addFrameIndex(FI).addImm(0).addMemOperand(MMO);
    AddDefaultPred(MIB);

    if (TargetRegisterInfo::isPhysicalRegister(DestReg))
      MIB.addReg(DestReg, RegState::ImplicitDefine);
    return;
  }

  ARMBaseInstrInfo::loadRegFromStackSlot(MBB, I, DestReg, FI, RC, TRI);
}

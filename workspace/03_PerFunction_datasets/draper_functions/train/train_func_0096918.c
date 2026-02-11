storeRegToStackSlot(MachineBasicBlock &MBB,
                                         MachineBasicBlock::iterator I,
                                         unsigned SrcReg, bool isKill,
                                         int FrameIndex,
                                         const TargetRegisterClass *RC,
                                         const TargetRegisterInfo *TRI) const
{
  DebugLoc DL;
  if (I != MBB.end() && !I->isDebugValue())
    DL = I->getDebugLoc();
  MachineFunction *MF = MBB.getParent();
  const MachineFrameInfo &MFI = *MF->getFrameInfo();
  MachineMemOperand *MMO = MF->getMachineMemOperand(
      MachinePointerInfo::getFixedStack(*MF, FrameIndex),
      MachineMemOperand::MOStore, MFI.getObjectSize(FrameIndex),
      MFI.getObjectAlignment(FrameIndex));
  BuildMI(MBB, I, DL, get(XCore::STWFI))
    .addReg(SrcReg, getKillRegState(isKill))
    .addFrameIndex(FrameIndex)
    .addImm(0)
    .addMemOperand(MMO);
}

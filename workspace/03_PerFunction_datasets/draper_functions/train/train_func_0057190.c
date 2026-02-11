loadRegFromStackSlot(MachineBasicBlock &MBB,
                                          MachineBasicBlock::iterator I,
                                          unsigned DestReg, int FrameIndex,
                                          const TargetRegisterClass *RC,
                                          const TargetRegisterInfo *TRI) const
{
  DebugLoc DL;
  if (I != MBB.end()) DL = I->getDebugLoc();
  BuildMI(MBB, I, DL, get(XCore::LDWFI), DestReg)
    .addFrameIndex(FrameIndex)
    .addImm(0);
}

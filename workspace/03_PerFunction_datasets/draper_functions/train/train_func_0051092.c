loadRegFromStackSlot(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator MI,
                                        unsigned DestReg, int FrameIdx,
                                        const TargetRegisterClass *RC,
                                        const TargetRegisterInfo *TRI) const {
  const MachineFunction &MF = *MBB.getParent();
  unsigned Alignment = RC->getSize() == 32 ? 32 : 16;
  bool isAligned = (TM.getFrameLowering()->getStackAlignment() >= Alignment) ||
    RI.canRealignStack(MF);
  unsigned Opc = getLoadRegOpcode(DestReg, RC, isAligned, TM);
  DebugLoc DL = MBB.findDebugLoc(MI);
  addFrameReference(BuildMI(MBB, MI, DL, get(Opc), DestReg), FrameIdx);
}

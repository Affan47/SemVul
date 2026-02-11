makeFrame(unsigned SP, int64_t FrameSize,
                                MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator I) const {
  DebugLoc DL;
  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo *MFI    = MF.getFrameInfo();
  const BitVector Reserved = RI.getReservedRegs(MF);
  bool SaveS2 = Reserved[Mips::S2];
  MachineInstrBuilder MIB;
  unsigned Opc = ((FrameSize <= 128) && !SaveS2)? Mips::Save16:Mips::SaveX16;
  MIB = BuildMI(MBB, I, DL, get(Opc));
  const std::vector<CalleeSavedInfo> &CSI = MFI->getCalleeSavedInfo();
  addSaveRestoreRegs(MIB, CSI);
  if (SaveS2)
    MIB.addReg(Mips::S2);
  if (isUInt<11>(FrameSize))
    MIB.addImm(FrameSize);
  else {
    int Base = 2040;

    int64_t Remainder = FrameSize - Base;
    MIB.addImm(Base);
    if (isInt<16>(-Remainder))
      BuildAddiuSpImm(MBB, I, -Remainder);
    else
      adjustStackPtrBig(SP, -Remainder, MBB, I, Mips::V0, Mips::V1);
  }
}

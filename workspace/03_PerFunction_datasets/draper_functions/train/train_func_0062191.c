emitPrologue(MachineFunction &MF) const {
  MachineBasicBlock &MBB = MF.front();
  MachineFrameInfo *MFI = MF.getFrameInfo();
  const SparcInstrInfo &TII =
    *static_cast<const SparcInstrInfo*>(MF.getTarget().getInstrInfo());
  MachineBasicBlock::iterator MBBI = MBB.begin();
  DebugLoc dl = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();


  int NumBytes = (int) MFI->getStackSize();


  NumBytes += 92;


  NumBytes = (NumBytes + 7) & ~7;
  NumBytes = -NumBytes;

  if (NumBytes >= -4096) {
    BuildMI(MBB, MBBI, dl, TII.get(SP::SAVEri), SP::O6)
      .addReg(SP::O6).addImm(NumBytes);
  } else {


    unsigned OffHi = (unsigned)NumBytes >> 10U;
    BuildMI(MBB, MBBI, dl, TII.get(SP::SETHIi), SP::G1).addImm(OffHi);

    BuildMI(MBB, MBBI, dl, TII.get(SP::ORri), SP::G1)
      .addReg(SP::G1).addImm(NumBytes & ((1 << 10)-1));
    BuildMI(MBB, MBBI, dl, TII.get(SP::SAVErr), SP::O6)
      .addReg(SP::O6).addReg(SP::G1);
  }
}

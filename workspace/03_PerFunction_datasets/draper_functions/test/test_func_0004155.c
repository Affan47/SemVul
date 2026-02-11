initMips16SPAliasReg(MachineFunction &MF) {
  MipsFunctionInfo *MipsFI = MF.getInfo<MipsFunctionInfo>();

  if (!MipsFI->mips16SPAliasRegSet())
    return;

  MachineBasicBlock &MBB = MF.front();
  MachineBasicBlock::iterator I = MBB.begin();
  const TargetInstrInfo &TII = *Subtarget->getInstrInfo();
  DebugLoc DL = I != MBB.end() ? I->getDebugLoc() : DebugLoc();
  unsigned Mips16SPAliasReg = MipsFI->getMips16SPAliasReg();

  BuildMI(MBB, I, DL, TII.get(Mips::MoveR3216), Mips16SPAliasReg)
    .addReg(Mips::SP);
}

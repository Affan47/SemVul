expandRegLargeImmPair(unsigned OrigReg, int OrigImm,
                                  unsigned& NewReg, int& NewImm,
                                  MachineBasicBlock& MBB,
                                  MachineBasicBlock::iterator I) {

  if (OrigImm < 0x8000 && OrigImm >= -0x8000) {
    NewReg = OrigReg;
    NewImm = OrigImm;
    return false;
  }

  MachineFunction* MF = MBB.getParent();
  const TargetInstrInfo *TII = MF->getTarget().getInstrInfo();
  DebugLoc DL = I->getDebugLoc();
  int ImmLo = (short)(OrigImm & 0xffff);
  int ImmHi = (((unsigned)OrigImm & 0xffff0000) >> 16) +
              ((OrigImm & 0x8000) != 0);


  BuildMI(MBB, I, DL, TII->get(Mips::NOAT));
  BuildMI(MBB, I, DL, TII->get(Mips::LUi), Mips::AT).addImm(ImmHi);
  BuildMI(MBB, I, DL, TII->get(Mips::ADDu), Mips::AT).addReg(OrigReg)
                                                     .addReg(Mips::AT);
  NewReg = Mips::AT;
  NewImm = ImmLo;

  return true;
}

replaceWithCompactBranch(MachineBasicBlock &MBB,
                                      Iter Branch, DebugLoc DL) {
  const MipsInstrInfo *TII =
      MBB.getParent()->getSubtarget<MipsSubtarget>().getInstrInfo();

  unsigned NewOpcode =
    (((unsigned) Branch->getOpcode()) == Mips::BEQ) ? Mips::BEQZC_MM
                                                    : Mips::BNEZC_MM;

  const MCInstrDesc &NewDesc = TII->get(NewOpcode);
  MachineInstrBuilder MIB = BuildMI(MBB, Branch, DL, NewDesc);

  MIB.addReg(Branch->getOperand(0).getReg());
  MIB.addMBB(Branch->getOperand(2).getMBB());

  Iter tmpIter = Branch;
  Branch = std::prev(Branch);
  MBB.erase(tmpIter);

  return Branch;
}

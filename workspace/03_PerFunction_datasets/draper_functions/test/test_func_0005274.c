ExpandFPMLxInstruction(MachineBasicBlock &MBB, MachineInstr *MI,
                                     unsigned MulOpc, unsigned AddSubOpc,
                                     bool NegAcc, bool HasLane) {
  unsigned DstReg = MI->getOperand(0).getReg();
  bool DstDead = MI->getOperand(0).isDead();
  unsigned AccReg = MI->getOperand(1).getReg();
  unsigned Src1Reg = MI->getOperand(2).getReg();
  unsigned Src2Reg = MI->getOperand(3).getReg();
  bool Src1Kill = MI->getOperand(2).isKill();
  bool Src2Kill = MI->getOperand(3).isKill();
  unsigned LaneImm = HasLane ? MI->getOperand(4).getImm() : 0;
  unsigned NextOp = HasLane ? 5 : 4;
  ARMCC::CondCodes Pred = (ARMCC::CondCodes)MI->getOperand(NextOp).getImm();
  unsigned PredReg = MI->getOperand(++NextOp).getReg();

  const MCInstrDesc &MCID1 = TII->get(MulOpc);
  const MCInstrDesc &MCID2 = TII->get(AddSubOpc);
  const MachineFunction &MF = *MI->getParent()->getParent();
  unsigned TmpReg = MRI->createVirtualRegister(
                      TII->getRegClass(MCID1, 0, TRI, MF));

  MachineInstrBuilder MIB = BuildMI(MBB, MI, MI->getDebugLoc(), MCID1, TmpReg)
    .addReg(Src1Reg, getKillRegState(Src1Kill))
    .addReg(Src2Reg, getKillRegState(Src2Kill));
  if (HasLane)
    MIB.addImm(LaneImm);
  MIB.addImm(Pred).addReg(PredReg);

  MIB = BuildMI(MBB, MI, MI->getDebugLoc(), MCID2)
    .addReg(DstReg, getDefRegState(true) | getDeadRegState(DstDead));

  if (NegAcc) {
    bool AccKill = MRI->hasOneNonDBGUse(AccReg);
    MIB.addReg(TmpReg, getKillRegState(true))
       .addReg(AccReg, getKillRegState(AccKill));
  } else {
    MIB.addReg(AccReg).addReg(TmpReg, getKillRegState(true));
  }
  MIB.addImm(Pred).addReg(PredReg);

  DEBUG({
      dbgs() << "Expanding: " << *MI;
      dbgs() << "  to:\n";
      MachineBasicBlock::iterator MII = MI;
      MII = std::prev(MII);
      MachineInstr &MI2 = *MII;
      MII = std::prev(MII);
      MachineInstr &MI1 = *MII;
      dbgs() << "    " << MI1;
      dbgs() << "    " << MI2;
   });

  MI->eraseFromParent();
  ++NumExpand;
}

fixupUnconditionalBr(ImmBranch &Br) {
  MachineInstr *MI = Br.MI;
  MachineBasicBlock *MBB = MI->getParent();
  MachineBasicBlock *DestBB = MI->getOperand(0).getMBB();

  unsigned BimmX16MaxDisp = ((1 << 16)-1) * 2;
  if (isBBInRange(MI, DestBB, BimmX16MaxDisp)) {
    Br.MaxDisp = BimmX16MaxDisp;
    MI->setDesc(TII->get(Mips::BimmX16));
  }
  else {


    DestBB->setAlignment(2);
    Br.MaxDisp = ((1<<24)-1) * 2;
    MI->setDesc(TII->get(Mips::JalB16));
  }
  BBInfo[MBB->getNumber()].Size += 2;
  adjustBBOffsetsAfter(MBB);
  HasFarJump = true;
  ++NumUBrFixed;

  DEBUG(dbgs() << "  Changed B to long jump " << *MI);

  return true;
}

FixUpImmediateBr(MachineFunction &MF, ImmBranch &Br) {
  MachineInstr *MI = Br.MI;
  MachineBasicBlock *DestBB = MI->getOperand(0).getMBB();


  if (BBIsInRange(MI, DestBB, Br.MaxDisp))
    return false;

  if (!Br.isCond)
    return FixUpUnconditionalBr(MF, Br);
  return FixUpConditionalBr(MF, Br);
}

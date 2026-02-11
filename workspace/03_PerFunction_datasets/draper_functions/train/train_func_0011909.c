isWorthBreakingCriticalEdge(MachineInstr *MI,
                                                 MachineBasicBlock *From,
                                                 MachineBasicBlock *To) {


  if (!CEBCandidates.insert(std::make_pair(From, To)))
    return true;

  if (!MI->isCopy() && !MI->getDesc().isAsCheapAsAMove())
    return true;


  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg()) continue;
    unsigned Reg = MO.getReg();
    if (Reg == 0 || !TargetRegisterInfo::isPhysicalRegister(Reg))
      continue;
    if (MRI->hasOneNonDBGUse(Reg))
      return true;
  }

  return false;
}

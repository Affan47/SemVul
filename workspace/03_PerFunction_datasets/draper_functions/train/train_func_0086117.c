isWorthBreakingCriticalEdge(MachineInstr *MI,
                                                 MachineBasicBlock *From,
                                                 MachineBasicBlock *To) {


  if (!CEBCandidates.insert(std::make_pair(From, To)).second)
    return true;

  if (!MI->isCopy() && !TII->isAsCheapAsAMove(MI))
    return true;


  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || !MO.isUse())
      continue;
    unsigned Reg = MO.getReg();
    if (Reg == 0)
      continue;


    if (TargetRegisterInfo::isPhysicalRegister(Reg))
      continue;


    if (MRI->hasOneNonDBGUse(Reg)) {


      MachineInstr *DefMI = MRI->getVRegDef(Reg);
      if (DefMI->getParent() == MI->getParent())
        return true;
    }
  }

  return false;
}

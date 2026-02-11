IsProfitableToHoist(MachineInstr &MI) {
  if (MI.isImplicitDef())
    return true;


  if (IsCheapInstruction(MI)) {
    if (!TII->isTriviallyReMaterializable(&MI, AA))
      return false;
  } else {


    DenseMap<unsigned, int> Cost;
    for (unsigned i = 0, e = MI.getDesc().getNumOperands(); i != e; ++i) {
      const MachineOperand &MO = MI.getOperand(i);
      if (!MO.isReg() || MO.isImplicit())
        continue;
      unsigned Reg = MO.getReg();
      if (!TargetRegisterInfo::isVirtualRegister(Reg))
        continue;

      unsigned RCId, RCCost;
      getRegisterClassIDAndCost(&MI, Reg, i, RCId, RCCost);
      if (MO.isDef()) {
        if (HasHighOperandLatency(MI, i, Reg)) {
          ++NumHighLatency;
          return true;
        }

        DenseMap<unsigned, int>::iterator CI = Cost.find(RCId);
        if (CI != Cost.end())
          CI->second += RCCost;
        else
          Cost.insert(std::make_pair(RCId, RCCost));
      } else if (isOperandKill(MO, MRI)) {


        DenseMap<unsigned, int>::iterator CI = Cost.find(RCId);
        if (CI != Cost.end())
          CI->second -= RCCost;
        else
          Cost.insert(std::make_pair(RCId, -RCCost));
      }
    }


    if (!CanCauseHighRegPressure(Cost)) {
      ++NumLowRP;
      return true;
    }


    if (AvoidSpeculation &&
        (!IsGuaranteedToExecute(MI.getParent()) && !MayCSE(&MI)))
      return false;


    if (!TII->isTriviallyReMaterializable(&MI, AA) &&
        !MI.isInvariantLoad(AA))
      return false;
  }


  for (unsigned i = 0, e = MI.getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI.getOperand(i);
    if (!MO.isReg() || !MO.isDef())
      continue;
    if (HasAnyPHIUse(MO.getReg()))
      return false;
  }

  return true;
}

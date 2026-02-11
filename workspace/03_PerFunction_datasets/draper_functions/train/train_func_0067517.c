IsProfitableToHoist(MachineInstr &MI) {
  if (MI.isImplicitDef())
    return true;


  bool CheapInstr = IsCheapInstruction(MI);
  bool CreatesCopy = HasLoopPHIUse(&MI);


  if (CheapInstr && CreatesCopy) {
    DEBUG(dbgs() << "Won't hoist cheap instr with loop PHI use: " << MI);
    return false;
  }


  if (TII->isTriviallyReMaterializable(&MI, AA))
    return true;


  for (unsigned i = 0, e = MI.getDesc().getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI.getOperand(i);
    if (!MO.isReg() || MO.isImplicit())
      continue;
    unsigned Reg = MO.getReg();
    if (!TargetRegisterInfo::isVirtualRegister(Reg))
      continue;
    if (MO.isDef() && HasHighOperandLatency(MI, i, Reg)) {
      DEBUG(dbgs() << "Hoist High Latency: " << MI);
      ++NumHighLatency;
      return true;
    }
  }


  auto Cost = calcRegisterCost(&MI, false,
                               false);


  if (!CanCauseHighRegPressure(Cost, CheapInstr)) {
    DEBUG(dbgs() << "Hoist non-reg-pressure: " << MI);
    ++NumLowRP;
    return true;
  }


  if (CreatesCopy) {
    DEBUG(dbgs() << "Won't hoist instr with loop PHI use: " << MI);
    return false;
  }


  if (AvoidSpeculation &&
      (!IsGuaranteedToExecute(MI.getParent()) && !MayCSE(&MI))) {
    DEBUG(dbgs() << "Won't speculate: " << MI);
    return false;
  }


  if (!TII->isTriviallyReMaterializable(&MI, AA) &&
      !MI.isInvariantLoad(AA)) {
    DEBUG(dbgs() << "Can't remat / high reg-pressure: " << MI);
    return false;
  }

  return true;
}

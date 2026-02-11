UpdateRegPressure(const MachineInstr *MI) {
  if (MI->isImplicitDef())
    return;

  SmallVector<unsigned, 4> Defs;
  for (unsigned i = 0, e = MI->getDesc().getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || MO.isImplicit())
      continue;
    unsigned Reg = MO.getReg();
    if (!TargetRegisterInfo::isVirtualRegister(Reg))
      continue;

    bool isNew = RegSeen.insert(Reg);
    if (MO.isDef())
      Defs.push_back(Reg);
    else if (!isNew && isOperandKill(MO, MRI)) {
      unsigned RCId, RCCost;
      getRegisterClassIDAndCost(MI, Reg, i, RCId, RCCost);
      if (RCCost > RegPressure[RCId])
        RegPressure[RCId] = 0;
      else
        RegPressure[RCId] -= RCCost;
    }
  }

  unsigned Idx = 0;
  while (!Defs.empty()) {
    unsigned Reg = Defs.pop_back_val();
    unsigned RCId, RCCost;
    getRegisterClassIDAndCost(MI, Reg, Idx, RCId, RCCost);
    RegPressure[RCId] += RCCost;
    ++Idx;
  }
}

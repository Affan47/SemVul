IsCPSRDead<MachineInstr>(MachineInstr *MI) {
  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || MO.isUndef() || MO.isUse())
      continue;
    if (MO.getReg() != ARM::CPSR)
      continue;
    if (!MO.isDead())
      return false;
  }

  return true;
}

DefinesOptionalPredicate(MachineInstr *MI, bool *CPSR) {
  if (!MI->hasOptionalDef())
    return false;


  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || !MO.isDef()) continue;
    if (MO.getReg() == ARM::CPSR)
      *CPSR = true;
  }
  return true;
}

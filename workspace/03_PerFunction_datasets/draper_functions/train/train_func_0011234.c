isSafeToDelete(MachineInstr &MI) {
  const MCInstrDesc &MCID = MI.getDesc();
  if (MCID.mayLoad() || MCID.mayStore() || MCID.isTerminator() ||
      MCID.isCall() || MCID.isBarrier() || MCID.isReturn() ||
      MI.isLabel() || MI.isDebugValue() ||
      MI.hasUnmodeledSideEffects())
    return false;


  if (MI.isInlineAsm())
    return false;

  for (unsigned i = 0, e = MI.getNumOperands(); i != e; ++i) {
    MachineOperand &MO = MI.getOperand(i);
    if (!MO.isReg() || !MO.getReg())
      continue;
    if (MO.isDef() && !MO.isDead())
      return false;
    if (MO.isUse() && MO.isKill())


      return false;
  }
  return true;
}

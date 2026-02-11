getMachineOpValue(const MCInst &MI,
                                             const MCOperand &MO) const {
  if (MO.isReg())
    return getMBlazeRegisterNumbering(MO.getReg());
  else if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());
  else if (MO.isExpr())
      return 0;
  else {
#ifndef NDEBUG
    errs() << MO;
#endif
    llvm_unreachable(0);
  }
  return 0;
}

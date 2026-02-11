getITInstrPredicate(const MachineInstr *MI, unsigned &PredReg) {
  unsigned Opc = MI->getOpcode();
  if (Opc == ARM::tBcc || Opc == ARM::t2Bcc)
    return ARMCC::AL;
  return llvm::getInstrPredicate(MI, PredReg);
}

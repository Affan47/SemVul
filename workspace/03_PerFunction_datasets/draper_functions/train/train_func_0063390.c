verifyInstruction(const MachineInstr *MI,
                                         StringRef &ErrInfo) const {
  if (convertAddSubFlagsOpcode(MI->getOpcode())) {
    ErrInfo = "Pseudo flag setting opcodes only exist in Selection DAG";
    return false;
  }
  return true;
}

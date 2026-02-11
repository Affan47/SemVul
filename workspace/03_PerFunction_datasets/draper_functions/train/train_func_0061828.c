isAliased(const MachineFrameInfo *MFI) const {
  if (this == getStack() ||
      this == getGOT() ||
      this == getConstantPool() ||
      this == getJumpTable())
    return false;
  llvm_unreachable("Unknown PseudoSourceValue!");
  return true;
}

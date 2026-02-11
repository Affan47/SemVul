areAllUsesSwizzeable(unsigned Reg) const {
  for (MachineRegisterInfo::use_instr_iterator It = MRI->use_instr_begin(Reg),
      E = MRI->use_instr_end(); It != E; ++It) {
    if (!canSwizzle(*It))
      return false;
  }
  return true;
}

dumpUses(unsigned Reg) const {
  for (use_iterator I = use_begin(Reg), E = use_end(); I != E; ++I)
    I.getOperand().getParent()->dump();
}

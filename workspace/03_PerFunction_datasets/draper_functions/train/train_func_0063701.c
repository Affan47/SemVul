delayHasHazard(MachineBasicBlock::iterator &candidate,
                           MachineBasicBlock::iterator &slot) {

  MachineBasicBlock::iterator a = candidate;
  MachineBasicBlock::iterator b = slot;
  MCInstrDesc desc = candidate->getDesc();


  bool a_is_memory = desc.mayLoad() || desc.mayStore();


  const unsigned aend = getLastRealOperand(a);
  const unsigned bend = getLastRealOperand(b);


  MachineBasicBlock::iterator m = a;
  for (++m; m != b; ++m) {
    for (unsigned aop = 0; aop<aend; ++aop) {
      bool aop_is_reg = a->getOperand(aop).isReg();
      if (!aop_is_reg) continue;

      bool aop_is_def = a->getOperand(aop).isDef();
      unsigned aop_reg = a->getOperand(aop).getReg();

      const unsigned mend = getLastRealOperand(m);
      for (unsigned mop = 0; mop<mend; ++mop) {
        bool mop_is_reg = m->getOperand(mop).isReg();
        if (!mop_is_reg) continue;

        bool mop_is_def = m->getOperand(mop).isDef();
        unsigned mop_reg = m->getOperand(mop).getReg();

        if (aop_is_def && (mop_reg == aop_reg))
            return true;
        else if (mop_is_def && (mop_reg == aop_reg))
            return true;
      }
    }


    if (a_is_memory && m->getDesc().mayStore())
      return true;
  }


  for (unsigned aop = 0; aop<aend; ++aop) {
    if (a->getOperand(aop).isReg()) {
      unsigned aop_reg = a->getOperand(aop).getReg();

      for (unsigned bop = 0; bop<bend; ++bop) {
        if (b->getOperand(bop).isReg() && !b->getOperand(bop).isImplicit()) {
          unsigned bop_reg = b->getOperand(bop).getReg();
          if (aop_reg == bop_reg)
            return true;
        }
      }
    }
  }

  return false;
}

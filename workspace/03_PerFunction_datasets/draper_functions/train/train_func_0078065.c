isSafeToClobberEFLAGS(MachineBasicBlock &MBB,
                                         MachineBasicBlock::iterator I) const {
  MachineBasicBlock::iterator E = MBB.end();


  MachineBasicBlock::iterator Iter = I;
  for (unsigned i = 0; Iter != E && i < 4; ++i) {
    bool SeenDef = false;
    for (unsigned j = 0, e = Iter->getNumOperands(); j != e; ++j) {
      MachineOperand &MO = Iter->getOperand(j);
      if (MO.isRegMask() && MO.clobbersPhysReg(X86::EFLAGS))
        SeenDef = true;
      if (!MO.isReg())
        continue;
      if (MO.getReg() == X86::EFLAGS) {
        if (MO.isUse())
          return false;
        SeenDef = true;
      }
    }

    if (SeenDef)

      return true;
    ++Iter;

    while (Iter != E && Iter->isDebugValue())
      ++Iter;
  }


  if (Iter == E) {
    for (MachineBasicBlock::succ_iterator SI = MBB.succ_begin(),
           SE = MBB.succ_end(); SI != SE; ++SI)
      if ((*SI)->isLiveIn(X86::EFLAGS))
        return false;
    return true;
  }

  MachineBasicBlock::iterator B = MBB.begin();
  Iter = I;
  for (unsigned i = 0; i < 4; ++i) {


    if (Iter == B)
      return !MBB.isLiveIn(X86::EFLAGS);

    --Iter;

    while (Iter != B && Iter->isDebugValue())
      --Iter;

    bool SawKill = false;
    for (unsigned j = 0, e = Iter->getNumOperands(); j != e; ++j) {
      MachineOperand &MO = Iter->getOperand(j);


      if (MO.isRegMask() && MO.clobbersPhysReg(X86::EFLAGS))
        SawKill = true;
      if (MO.isReg() && MO.getReg() == X86::EFLAGS) {
        if (MO.isDef()) return MO.isDead();
        if (MO.isKill()) SawKill = true;
      }
    }

    if (SawKill)


      return true;
  }


  return false;
}

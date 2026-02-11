delayHasHazard(MachineBasicBlock::iterator candidate,
                            bool &sawLoad,
                            bool &sawStore,
                            SmallSet<unsigned, 32> &RegDefs,
                            SmallSet<unsigned, 32> &RegUses)
{

  if (candidate->isImplicitDef() || candidate->isKill())
    return true;

  if (candidate->mayLoad()) {
    sawLoad = true;
    if (sawStore)
      return true;
  }

  if (candidate->mayStore()) {
    if (sawStore)
      return true;
    sawStore = true;
    if (sawLoad)
      return true;
  }

  for (unsigned i = 0, e = candidate->getNumOperands(); i!= e; ++i) {
    const MachineOperand &MO = candidate->getOperand(i);
    if (!MO.isReg())
      continue;

    unsigned Reg = MO.getReg();

    if (MO.isDef()) {

      if (IsRegInSet(RegDefs, Reg) || IsRegInSet(RegUses, Reg))
        return true;
    }
    if (MO.isUse()) {

      if (IsRegInSet(RegDefs, Reg))
        return true;
    }
  }
  return false;
}

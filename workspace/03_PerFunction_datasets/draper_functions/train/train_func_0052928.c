isUnpredicatedTerminator(const MachineInstr *MI) const {
  if (!MI->isTerminator())
    return false;


  if (MI->isBranch() && !MI->isBarrier())
    return true;

  return !isPredicated(MI);
}

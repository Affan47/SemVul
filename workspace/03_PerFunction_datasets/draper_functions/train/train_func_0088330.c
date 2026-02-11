canFallThrough() {
  MachineFunction::iterator Fallthrough = this;
  ++Fallthrough;

  if (Fallthrough == getParent()->end())
    return false;


  if (!isSuccessor(Fallthrough))
    return false;


  MachineBasicBlock *TBB = 0, *FBB = 0;
  SmallVector<MachineOperand, 4> Cond;
  const TargetInstrInfo *TII = getParent()->getTarget().getInstrInfo();
  if (TII->AnalyzeBranch(*this, TBB, FBB, Cond)) {


    return empty() || !back().getDesc().isBarrier() ||
           back().getDesc().isPredicable();
  }


  if (TBB == 0) return true;


  if (MachineFunction::iterator(TBB) == Fallthrough ||
      MachineFunction::iterator(FBB) == Fallthrough)
    return true;


  if (Cond.empty()) return false;


  return FBB == 0;
}

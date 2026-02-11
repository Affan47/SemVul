canFoldMemoryOperand(MachineInstr *MI,
                                         SmallVector<unsigned, 2> &Ops,
                                         bool ReMat) const {


  unsigned MRInfo = 0;
  SmallVector<unsigned, 2> FoldOps;
  if (FilterFoldedOps(MI, Ops, MRInfo, FoldOps))
    return false;


  if (ReMat && (MRInfo & VirtRegMap::isMod))
    return false;

  return tii_->canFoldMemoryOperand(MI, FoldOps);
}

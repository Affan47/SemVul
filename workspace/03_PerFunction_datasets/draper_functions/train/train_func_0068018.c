ProfitableToMerge(MachineBasicBlock *MBB1,
                              MachineBasicBlock *MBB2,
                              unsigned minCommonTailLength,
                              unsigned &CommonTailLen,
                              MachineBasicBlock::iterator &I1,
                              MachineBasicBlock::iterator &I2,
                              MachineBasicBlock *SuccBB,
                              MachineBasicBlock *PredBB) {
  CommonTailLen = ComputeCommonTailLength(MBB1, MBB2, I1, I2);
  if (CommonTailLen == 0)
    return false;
  DEBUG(dbgs() << "Common tail length of BB#" << MBB1->getNumber()
               << " and BB#" << MBB2->getNumber() << " is " << CommonTailLen
               << '\n');


  if (MBB1 == PredBB || MBB2 == PredBB) {
    MachineBasicBlock::iterator I;
    unsigned NumTerms = CountTerminators(MBB1 == PredBB ? MBB2 : MBB1, I);
    if (CommonTailLen > NumTerms)
      return true;
  }


  if (MBB1->isLayoutSuccessor(MBB2) && I2 == MBB2->begin())
    return true;
  if (MBB2->isLayoutSuccessor(MBB1) && I1 == MBB1->begin())
    return true;


  unsigned EffectiveTailLen = CommonTailLen;
  if (SuccBB && MBB1 != PredBB && MBB2 != PredBB &&
      !MBB1->back().getDesc().isBarrier() &&
      !MBB2->back().getDesc().isBarrier())
    ++EffectiveTailLen;


  if (EffectiveTailLen >= minCommonTailLength)
    return true;


  MachineFunction *MF = MBB1->getParent();
  if (EffectiveTailLen >= 2 &&
      MF->getFunction()->hasFnAttr(Attribute::OptimizeForSize) &&
      (I1 == MBB1->begin() || I2 == MBB2->begin()))
    return true;

  return false;
}

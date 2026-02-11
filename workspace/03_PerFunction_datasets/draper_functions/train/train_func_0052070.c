CanSelectOperandBeMappingIntoPredBlock(const Value *V,
                                                   const SelectInst &SI) {


  const Instruction *I = dyn_cast<Instruction>(V);
  if (!I) return true;


  const PHINode *CondPHI = cast<PHINode>(SI.getCondition());

  if (const PHINode *VP = dyn_cast<PHINode>(I))
    if (VP->getParent() == CondPHI->getParent())
      return true;


  if (SI.getParent() == CondPHI->getParent() &&
      I->getParent() != CondPHI->getParent())
    return true;


  return false;
}

getShuffleMask(const ShuffleVectorInst *SVI) {
  unsigned NElts = SVI->getType()->getNumElements();
  if (isa<ConstantAggregateZero>(SVI->getOperand(2)))
    return std::vector<int>(NElts, 0);
  if (isa<UndefValue>(SVI->getOperand(2)))
    return std::vector<int>(NElts, -1);

  std::vector<int> Result;
  const ConstantVector *CP = cast<ConstantVector>(SVI->getOperand(2));
  for (User::const_op_iterator i = CP->op_begin(), e = CP->op_end(); i!=e; ++i)
    if (isa<UndefValue>(*i))
      Result.push_back(-1);
    else
      Result.push_back(cast<ConstantInt>(*i)->getZExtValue());
  return Result;
}

getRank(Value *V) {
  Instruction *I = dyn_cast<Instruction>(V);
  if (!I) {
    if (isa<Argument>(V)) return ValueRankMap[V];
    return 0;
  }

  if (unsigned Rank = ValueRankMap[I])
    return Rank;


  unsigned Rank = 0, MaxRank = RankMap[I->getParent()];
  for (unsigned i = 0, e = I->getNumOperands();
       i != e && Rank != MaxRank; ++i)
    Rank = std::max(Rank, getRank(I->getOperand(i)));


  if  (!BinaryOperator::isNot(I) && !BinaryOperator::isNeg(I) &&
       !BinaryOperator::isFNeg(I))
    ++Rank;

  DEBUG(dbgs() << "Calculated Rank[" << V->getName() << "] = " << Rank << "\n");

  return ValueRankMap[I] = Rank;
}

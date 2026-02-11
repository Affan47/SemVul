hasLoopInvariantOperands(Instruction *I) const {
  for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i)
    if (!isLoopInvariant(I->getOperand(i)))
      return false;

  return true;
}

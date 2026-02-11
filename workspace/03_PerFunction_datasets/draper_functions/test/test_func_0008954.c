FindInOperandList(SmallVectorImpl<ValueEntry> &Ops, unsigned i,
                                  Value *X) {
  unsigned XRank = Ops[i].Rank;
  unsigned e = Ops.size();
  for (unsigned j = i+1; j != e && Ops[j].Rank == XRank; ++j) {
    if (Ops[j].Op == X)
      return j;
    if (Instruction *I1 = dyn_cast<Instruction>(Ops[j].Op))
      if (Instruction *I2 = dyn_cast<Instruction>(X))
        if (I1->isIdenticalTo(I2))
          return j;
  }

  for (unsigned j = i-1; j != ~0U && Ops[j].Rank == XRank; --j) {
    if (Ops[j].Op == X)
      return j;
    if (Instruction *I1 = dyn_cast<Instruction>(Ops[j].Op))
      if (Instruction *I2 = dyn_cast<Instruction>(X))
        if (I1->isIdenticalTo(I2))
          return j;
  }
  return i;
}

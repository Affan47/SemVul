insnDominatedBy(const Instruction *later,
                                    const Instruction *early) const
{
   if (early->bb == later->bb)
      return early->serial < later->serial;
   return later->bb->dominatedBy(early->bb);
}

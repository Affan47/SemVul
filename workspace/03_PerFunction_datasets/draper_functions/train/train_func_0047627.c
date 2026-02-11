nextPermutation(Symbol *permutation, unsigned blockSize)
{


  unsigned upLvl = blockSize - 1;
  {
    Symbol maxSymInSuf = permutation[blockSize - 1];
    do
    {
      if (upLvl == 0 || maxSymInSuf > permutation[--upLvl])
        break;
      if (permutation[upLvl] > maxSymInSuf)
        maxSymInSuf = permutation[upLvl];
    } while (1);
  }


  {
    Symbol saved = permutation[upLvl];
    Symbol swap = permutation[upLvl + 1];
    unsigned swapIdx = upLvl + 1;
    unsigned i;
    for (i = swapIdx + 1; i < blockSize; ++i)
    {
      if (permutation[i] > saved && permutation[i] < swap)
        swap = permutation[i], swapIdx = i;
    }
    permutation[upLvl] = swap;
    permutation[swapIdx] = saved;
  }
  for (++upLvl;upLvl < blockSize - 1; ++upLvl)
  {

    unsigned i, minIdx = upLvl;
    Symbol minSym = permutation[upLvl];
    for (i = upLvl + 1; i < blockSize; ++i)
      if (permutation[i] < minSym)
        minSym = permutation[i], minIdx = i;
    permutation[minIdx] = permutation[upLvl];
    permutation[upLvl] = minSym;
  }
}

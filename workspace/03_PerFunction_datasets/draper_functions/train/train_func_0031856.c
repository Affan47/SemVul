agrsum(Aword atr, Aword whr)
#else
Aint agrsum(atr, whr)
     Aword atr, whr;
#endif
{
  Aword i;
  Aint sum = 0;

  for (i = OBJMIN; i <= OBJMAX; i++) {
    if (isLoc(whr)) {
      if (where(i) == whr)
	sum += attribute(i, atr);
    } else if (objs[i-OBJMIN].loc == whr)
      sum += attribute(i, atr);
  }
  return(sum);
}

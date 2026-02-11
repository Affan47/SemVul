finalizefmfrequencies(Fmindex *fm)
{
  unsigned int j;
  unsigned long i, *freqptr;

  for (j = 2U; j <= fm->mapsize; j++)
  {
    fm->tfreq[j] += fm->tfreq[j - 1];
  }
  freqptr = fm->superbfreq;
  for (j = 0; j < fm->mapsize; j++)
  {
    for (i = (unsigned long) 2; i < fm->nofsuperblocks; i++)
    {
      freqptr[i] += freqptr[i-1];
    }
    freqptr += fm->nofsuperblocks;
  }
}

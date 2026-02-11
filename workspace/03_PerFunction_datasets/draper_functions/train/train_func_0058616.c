gt_showPatterndistribution(const Enumpatterniterator *epi)
{
  unsigned long i;
  double addprob, probsum = 0.0;

  printf("# %lu pattern with the following length distribution:\n",
         epi->samplecount);
  for (i=epi->minpatternlen; i<=epi->maxpatternlen; i++)
  {
    if (epi->patternstat[i] > 0)
    {
      addprob = (double) epi->patternstat[i] / epi->samplecount;
      probsum += addprob;
      printf("# %lu: %lu (prob=%.4f,cumulative=%.4f)\n",
             i,
             epi->patternstat[i],
             addprob,
             probsum);
    }
  }
}

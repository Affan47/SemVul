cmaes_SamplePopulation(cmaes_t *t)
{
  int iNk, i, j, N=t->sp.N;
  int flgdiag = ((t->sp.diagonalCov == 1) || (t->sp.diagonalCov >= t->gen));
  double sum;
  double const *xmean = t->rgxmean;


  if (!t->flgEigensysIsUptodate) {
    if (!flgdiag)
      cmaes_UpdateEigensystem(t, 0);
    else {
        for (i = 0; i < N; ++i)
          t->rgD[i] = sqrt(t->C[i][i]);
        t->minEW = douSquare(rgdouMin(t->rgD, N));
        t->maxEW = douSquare(rgdouMax(t->rgD, N));
        t->flgEigensysIsUptodate = 1;
        timings_start(&t->eigenTimings);
      }
  }


  TestMinStdDevs(t);

  for (iNk = 0; iNk < t->sp.lambda; ++iNk)
    {
      for (i = 0; i < N; ++i)
        if (flgdiag)
          t->rgrgx[iNk][i] = xmean[i] + t->sigma * t->rgD[i] * random_Gauss(&t->rand);
        else
          t->rgdTmp[i] = t->rgD[i] * random_Gauss(&t->rand);
      if (!flgdiag)

        for (i = 0; i < N; ++i) {
          for (j = 0, sum = 0.; j < N; ++j)
            sum += t->B[i][j] * t->rgdTmp[j];
          t->rgrgx[iNk][i] = xmean[i] + t->sigma * sum;
        }
    }
  if(t->state == 3 || t->gen == 0)
    ++t->gen;
  t->state = 1;

  return(t->rgrgx);
}

cmaes_exit(cmaes_t *t)
{
  int i, N = t->sp.N;
  t->state = -1;
  free( t->rgpc);
  free( t->rgps);
  free( t->rgdTmp);
  free( t->rgBDz);
  free( --t->rgxmean);
  free( --t->rgxold);
  free( --t->rgxbestever);
  free( --t->rgout);
  free( t->rgD);
  for (i = 0; i < N; ++i) {
    free( t->C[i]);
    free( t->B[i]);
  }
  for (i = 0; i < t->sp.lambda; ++i)
    free( --t->rgrgx[i]);
  free( t->rgrgx);
  free( t->C);
  free( t->B);
  free( t->index);
  free( t->publicFitness);
  free( --t->rgFuncValue);
  free( --t->arFuncValueHist);
  random_exit (&t->rand);
  readpara_exit (&t->sp);
}

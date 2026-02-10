get_eigs(int n, ergo_real* M, ergo_real* bestVector, ergo_real* eigValListResult)
{
  int lwork = 3*n*n;
  ergo_real* work = new ergo_real[lwork];
  ergo_real* eigvalList = new ergo_real[n];
  ergo_real* A = new ergo_real[n*n];
  memcpy(A, M, n*n*sizeof(ergo_real));
  int info = 0;
  mat::syev("V", "U", &n, A,
            &n, eigvalList, work, &lwork,
            &info);
  if(info != 0)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_CI, "error in syev, info = %i", info);
      exit(0);
    }

#if 0
  for(int i = 0; i < n; i++)
    do_output(LOG_CAT_INFO, LOG_AREA_CI, "get_eigs eigenValue %5i: %22.11f", i, (double)eigvalList[i]);
#endif

  if(bestVector)
    {
      for(int i = 0; i < n; i++)
	bestVector[i] = A[0*n+i];
    }

  if(eigValListResult)
    {
      for(int i = 0; i < n; i++)
	eigValListResult[i] = eigvalList[i];
    }

  ergo_real result = eigvalList[0];

  delete [] work;
  delete [] eigvalList;
  delete [] A;

  return result;
}

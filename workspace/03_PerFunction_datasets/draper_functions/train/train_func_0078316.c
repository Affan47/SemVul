CreatePlan7Matrix(int N, int M, int padN, int padM)
{
  struct dpmatrix_s *mx;
  int i;

  mx          = (struct dpmatrix_s *) MallocOrDie (sizeof(struct dpmatrix_s));
  mx->xmx     = (int **) MallocOrDie (sizeof(int *) * (N+1));
  mx->mmx     = (int **) MallocOrDie (sizeof(int *) * (N+1));
  mx->imx     = (int **) MallocOrDie (sizeof(int *) * (N+1));
  mx->dmx     = (int **) MallocOrDie (sizeof(int *) * (N+1));
  mx->xmx_mem = (void *) MallocOrDie (sizeof(int) * ((N+1)*5));
  mx->mmx_mem = (void *) MallocOrDie (sizeof(int) * ((N+1)*(M+2)));
  mx->imx_mem = (void *) MallocOrDie (sizeof(int) * ((N+1)*(M+2)));
  mx->dmx_mem = (void *) MallocOrDie (sizeof(int) * ((N+1)*(M+2)));


  mx->xmx[0] = (int *) mx->xmx_mem;
  mx->mmx[0] = (int *) mx->mmx_mem;
  mx->imx[0] = (int *) mx->imx_mem;
  mx->dmx[0] = (int *) mx->dmx_mem;
  for (i = 1; i <= N; i++)
    {
      mx->xmx[i] = mx->xmx[0] + (i*5);
      mx->mmx[i] = mx->mmx[0] + (i*(M+2));
      mx->imx[i] = mx->imx[0] + (i*(M+2));
      mx->dmx[i] = mx->dmx[0] + (i*(M+2));
    }

  mx->maxN = N;
  mx->maxM = M;
  mx->padN = padN;
  mx->padM = padM;

  return mx;
}

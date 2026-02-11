cm_mx_Create(int M)
{
  int     status;
  CM_MX *mx = NULL;
  int     v;
  int allocL = 1;
  int allocW = 1;


  ESL_ALLOC(mx, sizeof(CM_MX));
  mx->dp     = NULL;
  mx->dp_mem = NULL;


  ESL_ALLOC(mx->dp,  sizeof(float **) * (M+1));


  ESL_ALLOC(mx->dp_mem,  sizeof(float) * (M+1) * (allocL) * (allocW));

  for (v = 0; v < M; v++) {
    ESL_ALLOC(mx->dp[v], sizeof(float *) * (allocL));
    mx->dp[v][0]  = mx->dp_mem + v * (allocL) * (allocW);
  }

  ESL_ALLOC(mx->dp[M], sizeof(float *) * (allocL));
  mx->dp[M][0]  = mx->dp_mem + M * (allocL) * (allocW);

  mx->M              = M;
  mx->ncells_alloc   = (M+1)*(allocL)*(allocW);
  mx->L              = allocL;


  mx->size_Mb = (float)
    (sizeof(CM_MX)                           +
     (mx->M+1)    * sizeof(float **)         +
     mx->ncells_alloc * sizeof(float)        +
     (mx->M+1) * allocL * sizeof(float *));
  mx->size_Mb *= 0.000001;

  return mx;

 ERROR:
  if (mx != NULL) cm_mx_Destroy(mx);
  return NULL;
}

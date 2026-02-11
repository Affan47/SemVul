cm_mx_Destroy(CM_MX *mx)
{
  if (mx == NULL) return;
  int v;

  if (mx->dp != NULL) {
    for (v = 0; v <= mx->M; v++)
      if(mx->dp[v] != NULL) free(mx->dp[v]);
  }
  free(mx->dp);

  if (mx->dp_mem  != NULL)  free(mx->dp_mem);
  free(mx);
  return;
}

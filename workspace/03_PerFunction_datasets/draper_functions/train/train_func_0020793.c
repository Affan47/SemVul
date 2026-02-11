FChiSquareFit(float *f1, float *f2, int N)
{
  int    i;
  float diff;
  float chisq = 0.0;
  int    n;
  double qax;

  n = 0;
  for (i = 0; i < N; i++)
    {
      if (f1[i] == 0. && f2[i] == 0.) continue;
      diff = f1[i] - f2[i];
      chisq += diff * diff / (f1[i]+f2[i]);
      n++;
    }

  if (n > 1)
    {
      if(esl_stats_IncompleteGamma(((float) n-1.)/2., chisq/2., NULL, &qax) != eslOK)
	cm_Fail("ERROR in FChiSquareFit() call to esl_stats_IncompleteGamma()");
      return (float) qax;
    }
  else
    return -1.;
}

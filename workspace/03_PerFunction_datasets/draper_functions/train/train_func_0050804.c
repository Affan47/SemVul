gmx_testpattern(P7_GMX *gx, int M, int L)
{
  int i,k,s,n, n2;


  n = 0;
  for (i = 0; i <= L; i++)
    for (k = 0; k <= M; k++)
      for (s = 0; s < p7G_NSCELLS; s++)
	gx->dp[i][k*p7G_NSCELLS+s] = n++;


  n = 0;
  for (i = 0; i <= L; i++)
    for (k = 0; k <= M; k++)
      for (s = 0; s < p7G_NSCELLS; s++)
		{
		  if (gx->dp[i][k*p7G_NSCELLS+s] != n) esl_fatal("gmx unit test failed: test pattern corrupted");
		  n++;
		}


  if (gx->allocR == gx->validR && gx->ncells == gx->validR*gx->allocW)
  {
      n2 = 0;
      for (i = 0; i < gx->ncells; i++)
		for (s = 0; s < p7G_NSCELLS; s++)
		  {
			if (gx->dp_mem[i*p7G_NSCELLS+s] != n2) esl_fatal("gmx unit test failed: test pattern corrupted (2nd test)");
			n2++;
		  }

      if (n != n2) esl_fatal("gmx unit test failed: unexpected # of cells");
  }
}

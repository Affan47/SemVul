p7_GForwardCheckpointed(const ESL_DSQ *dsq, int L, const P7_PROFILE *gm, P7_GMXCHK *gxc, float *opt_sc)
{
  float *dpc;
  float *dpp;
  int    M   = gm->M;
  int    w;
  int    b;
  int    i,k;


  dpc = dpp = gxc->dp[gxc->R0-1];
  for (k = 0; k < (M+1)*p7G_NSCELLS; k++)
    *dpc++ = -eslINFINITY;
  *dpc++ = -eslINFINITY;
  *dpc++ = 0;
  *dpc++ = -eslINFINITY;
  *dpc++ = -eslINFINITY;
  *dpc++ = gm->xsc[p7P_N][p7P_MOVE];
  *dpc++ = -eslINFINITY;
  *dpc   = -eslINFINITY;


  for (i = 1; i <= gxc->La; i++)
    {
      dpc = gxc->dp[gxc->R0+gxc->R]; gxc->R++;
      forward_row(dsq, gm, gxc, dpp, dpc, i);
      dpp = dpc;
    }


  for (b = gxc->Rb + gxc->Rc, w = (gxc->Rb ? gxc->Lb : gxc->Rc+1); i <= L; i++)
    {
      if (! (--w))
	{
	  dpc = gxc->dp[gxc->R0+gxc->R]; gxc->R++;
	  w=b;
	  b--;
	}
      else
	dpc =  gxc->dp[i%2];

      forward_row(dsq, gm, gxc, dpp, dpc, i);
      dpp = dpc;
    }

  gxc->M = M;
  gxc->L = L;
  gxc->R = gxc->Ra + gxc->Rb + gxc->Rc;
  if (opt_sc) *opt_sc = gxc->dp[gxc->R0+gxc->R-1][(M+1)*p7G_NSCELLS + p7GC_C] + gm->xsc[p7P_C][p7P_MOVE];
  return eslOK;
}

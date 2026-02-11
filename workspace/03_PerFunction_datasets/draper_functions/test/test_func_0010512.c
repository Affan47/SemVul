scoring_comparison(ESL_DSQ *dsq, int L, P7_PROFILE *gm, P7_GMX *gx, P7_GMXCHK *gxc, P7_GBANDS *bnd)
{
  char  msg[]     = "generic_fwdback_chk: score comparison test failure";
  float tolerance = 0.01;
  float fsc1, fsc2;
  float bsc1, bsc2;

  if ( p7_gmx_GrowTo(gx, gm->M, L)                      != eslOK) esl_fatal(msg);
  if ( p7_gmxchk_GrowTo(gxc, gm->M, L)                  != eslOK) esl_fatal(msg);

  if ( p7_GForward(dsq, L, gm, gx, &fsc1)                    != eslOK) esl_fatal(msg);
  if ( p7_gmx_Reuse(gx)                                      != eslOK) esl_fatal(msg);
  if ( p7_GBackward(dsq, L, gm, gx, &bsc1)                   != eslOK) esl_fatal(msg);
  if ( p7_GForwardCheckpointed (dsq, L, gm, gxc,      &fsc2) != eslOK) esl_fatal(msg);
  if ( p7_GBackwardCheckpointed(dsq, L, gm, gxc, bnd, &bsc2) != eslOK) esl_fatal(msg);

  if ( fabs(fsc1-bsc1) > tolerance) esl_fatal(msg);
  if ( fabs(fsc1-fsc2) > tolerance) esl_fatal(msg);
  if ( fabs(bsc1-bsc2) > tolerance) esl_fatal(msg);

  if ( p7_gmx_Reuse(gx)     != eslOK) esl_fatal(msg);
  if ( p7_gmxchk_Reuse(gxc) != eslOK) esl_fatal(msg);
  if ( p7_gbands_Reuse(bnd) != eslOK) esl_fatal(msg);
}

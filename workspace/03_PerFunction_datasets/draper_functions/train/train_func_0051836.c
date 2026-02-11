emit_sequences(ESL_GETOPTS *go, FILE *ofp, int outfmt, ESL_RANDOMNESS *r, P7_HMM *hmm)
{
  ESL_SQ     *sq           = NULL;
  P7_TRACE   *tr           = NULL;
  P7_BG      *bg           = NULL;
  P7_PROFILE *gm           = NULL;
  int         do_profile   = esl_opt_GetBoolean(go, "-p");
  int         N            = esl_opt_GetInteger(go, "-N");
  int         L            = esl_opt_GetInteger(go, "-L");
  int         mode;
  int         nseq;
  int         status;

  if      (esl_opt_GetBoolean(go, "--local"))     mode = p7_LOCAL;
  else if (esl_opt_GetBoolean(go, "--unilocal"))  mode = p7_UNILOCAL;
  else if (esl_opt_GetBoolean(go, "--glocal"))    mode = p7_GLOCAL;
  else if (esl_opt_GetBoolean(go, "--uniglocal")) mode = p7_UNIGLOCAL;

  if ((sq = esl_sq_CreateDigital(hmm->abc))      == NULL)  esl_fatal("failed to allocate sequence");
  if ((tr = p7_trace_Create())                   == NULL)  esl_fatal("failed to allocate trace");
  if ((bg = p7_bg_Create(hmm->abc))              == NULL)  esl_fatal("failed to create null model");
  if ((gm = p7_profile_Create(hmm->M, hmm->abc)) == NULL)  esl_fatal("failed to create profile");

  if (p7_ProfileConfig(hmm, bg, gm, L, mode)     != eslOK) esl_fatal("failed to configure profile");
  if (p7_bg_SetLength(bg, L)                     != eslOK) esl_fatal("failed to reconfig null model length");
  if (p7_hmm_Validate    (hmm, NULL, 0.0001)     != eslOK) esl_fatal("whoops, HMM is bad!");
  if (p7_profile_Validate(gm,  NULL, 0.0001)     != eslOK) esl_fatal("whoops, profile is bad!");

  for (nseq = 1; nseq <= N; nseq++)
    {
      if (do_profile) status = p7_ProfileEmit(r, hmm, gm, bg, sq, tr);
      else            status = p7_CoreEmit   (r, hmm, sq, tr);
      if (status)  esl_fatal("Failed to emit sequence\n");

      status = esl_sq_FormatName(sq, "%s-sample%d", hmm->name, nseq);
      if (status) esl_fatal("Failed to set sequence name\n");

      status = esl_sqio_Write(ofp, sq, outfmt, FALSE);
      if (status != eslOK) esl_fatal("Failed to write sequence\n");

      p7_trace_Reuse(tr);
      esl_sq_Reuse(sq);
    }

  esl_sq_Destroy(sq);
  p7_trace_Destroy(tr);
  p7_bg_Destroy(bg);
  p7_profile_Destroy(gm);
  return;
}

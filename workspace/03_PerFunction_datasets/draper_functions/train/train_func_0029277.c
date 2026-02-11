parse_results(char *resfile, int **pni, ESL_KEYHASH *qkh, ESL_KEYHASH *poskh, ESL_KEYHASH *negkh, struct result_s **ret_r, int *ret_nr)
{
  ESL_FILEPARSER  *efp    = NULL;
  char            *tok    = NULL;
  char            *target = NULL;
  char            *query  = NULL;
  int              toklen;
  int              qlen, tlen;
  struct result_s *rp     = NULL;
  int              ralloc = 0;
  int              nr     = 0;

  if (esl_fileparser_Open(resfile, NULL, &efp) != eslOK) esl_fatal("failed to open pmark results file %s", resfile);
  esl_fileparser_SetCommentChar(efp, '#');

  if ((rp = malloc(sizeof(struct result_s) * 256)) == NULL) esl_fatal("malloc failed");
  ralloc = 256;

  while (esl_fileparser_NextLine(efp) == eslOK)
    {
      if (nr == ralloc) {
	if ((rp = realloc(rp, sizeof(struct result_s) * ralloc * 2)) == NULL) esl_fatal("realloc failed");
	ralloc *= 2;
      }

      if (esl_fileparser_GetTokenOnLine(efp, &tok,    &toklen) != eslOK) esl_fatal("failed to parse line %d of %s", efp->linenumber, resfile);
      rp[nr].E = atof(tok);
      if (esl_fileparser_GetTokenOnLine(efp, &tok,    &toklen) != eslOK) esl_fatal("failed to parse line %d of %s", efp->linenumber, resfile);
      if (esl_fileparser_GetTokenOnLine(efp, &target, &tlen)   != eslOK) esl_fatal("failed to parse line %d of %s", efp->linenumber, resfile);
      if (esl_fileparser_GetTokenOnLine(efp, &query,  &qlen)   != eslOK) esl_fatal("failed to parse line %d of %s", efp->linenumber, resfile);
      if (esl_keyhash_Lookup(qkh, query, qlen, &(rp[nr].qidx)) != eslOK) esl_fatal("failed to find query model %s in hash", query);
      rp[nr].class = classify_pair_by_names(query, target);

      if (rp[nr].class == -1)
	{
	  if (esl_keyhash_Lookup(negkh, target, tlen, &(rp[nr].tidx)) != eslOK) esl_fatal("failed to find target seq  %s in hash", target);
	  rp[nr].tidx  += esl_keyhash_GetNumber(poskh);
	}
      else
	{
	  if (esl_keyhash_Lookup(poskh, target, tlen, &(rp[nr].tidx)) != eslOK) esl_fatal("failed to find target seq  %s in hash", target);
	}
      nr++;
    }

  *ret_r  = rp;
  *ret_nr = nr;
  esl_fileparser_Close(efp);
  return eslOK;
}

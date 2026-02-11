parse_tblfile(char *tblfile, ESL_KEYHASH *kh)
{
  ESL_FILEPARSER *efp = NULL;
  char           *tok = NULL;
  int             toklen;

  if (esl_fileparser_Open(tblfile, NULL, &efp) != eslOK) esl_fatal("failed to open pmark table %s", tblfile);
  esl_fileparser_SetCommentChar(efp, '#');

  while (esl_fileparser_NextLine(efp) == eslOK)
    {
      if (esl_fileparser_GetTokenOnLine(efp, &tok, &toklen) != eslOK) esl_fatal("failed to parse line %d of %s", efp->linenumber, tblfile);
      if (esl_keyhash_Store(kh, tok, toklen, NULL)          != eslOK) esl_fatal("failed to add %s to seq index", tok);
    }
  esl_fileparser_Close(efp);
  return eslOK;
}

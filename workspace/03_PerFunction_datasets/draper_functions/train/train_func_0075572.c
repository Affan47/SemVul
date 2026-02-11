p7_hmmfile_OpenBuffer(char *buffer, int size, P7_HMMFILE **ret_hfp)
{
  P7_HMMFILE *hfp     = NULL;
  int         status;
  char       *tok;
  int         toklen;

  ESL_ALLOC(hfp, sizeof(P7_HMMFILE));
  hfp->f            = NULL;
  hfp->fname        = NULL;
  hfp->do_gzip      = FALSE;
  hfp->do_stdin     = FALSE;
  hfp->newly_opened = TRUE;
  hfp->is_pressed   = FALSE;
#ifdef HMMER_THREADS
  hfp->syncRead     = FALSE;
#endif
  hfp->parser       = NULL;
  hfp->efp          = NULL;
  hfp->ffp          = NULL;
  hfp->pfp          = NULL;
  hfp->ssi          = NULL;
  hfp->errbuf[0]    = '\0';

  if ((hfp->efp = esl_fileparser_CreateMapped(buffer, size))         == NULL)   { status = eslEMEM; goto ERROR; }
  if ((status = esl_fileparser_SetCommentChar(hfp->efp, '#'))        != eslOK)  goto ERROR;
  if ((status = esl_fileparser_GetToken(hfp->efp, &tok, &toklen))    != eslOK)  goto ERROR;

  if      (strcmp("HMMER3/f", tok) == 0) { hfp->format = p7_HMMFILE_3f; hfp->parser = read_asc30hmm; }
  else if (strcmp("HMMER3/e", tok) == 0) { hfp->format = p7_HMMFILE_3e; hfp->parser = read_asc30hmm; }
  else if (strcmp("HMMER3/d", tok) == 0) { hfp->format = p7_HMMFILE_3d; hfp->parser = read_asc30hmm; }
  else if (strcmp("HMMER3/c", tok) == 0) { hfp->format = p7_HMMFILE_3c; hfp->parser = read_asc30hmm; }
  else if (strcmp("HMMER3/b", tok) == 0) { hfp->format = p7_HMMFILE_3b; hfp->parser = read_asc30hmm; }
  else if (strcmp("HMMER3/a", tok) == 0) { hfp->format = p7_HMMFILE_3a; hfp->parser = read_asc30hmm; }
  else if (strcmp("HMMER2.0", tok) == 0) { hfp->format = p7_HMMFILE_20; hfp->parser = read_asc20hmm; }

  if (hfp->parser == NULL) { status = eslEFORMAT; goto ERROR; }

  *ret_hfp = hfp;
  return eslOK;

 ERROR:
  if (hfp     != NULL) p7_hmmfile_Close(hfp);
  *ret_hfp = NULL;
  if      (status == eslEMEM)       return status;
  else if (status == eslENOTFOUND)  return status;
  else                              return eslEFORMAT;
}

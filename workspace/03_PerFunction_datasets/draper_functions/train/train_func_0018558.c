esl_msafile_a2m_GuessAlphabet(ESLX_MSAFILE *afp, int *ret_type)
{
  int       alphatype     = eslUNKNOWN;
  esl_pos_t anchor        = -1;
  int       threshold[3]  = { 500, 5000, 50000 };
  int       nsteps        = 3;
  int       step          = 0;
  int       nres          = 0;
  int       x;
  int64_t   ct[26];
  char     *p;
  esl_pos_t n, pos;
  int       status;

  for (x = 0; x < 26; x++) ct[x] = 0;

  anchor = esl_buffer_GetOffset(afp->bf);
  if ((status = esl_buffer_SetAnchor(afp->bf, anchor)) != eslOK) { status = eslEINCONCEIVABLE; goto ERROR; }

  while ( (status = esl_buffer_GetLine(afp->bf, &p, &n)) == eslOK)
    {
      while (n && isspace(*p)) { p++; n--; }
      if    (!n || *p == '>') continue;

      for (pos = 0; pos < n; pos++)
	if (isalpha(p[pos])) {
	  x = toupper(p[pos]) - 'A';
	  ct[x]++;
	  nres++;
	}


      if (step < nsteps && nres > threshold[step]) {
	if ((status = esl_abc_GuessAlphabet(ct, &alphatype)) == eslOK) goto DONE;
	step++;
      }
    }
  if (status != eslEOF) goto ERROR;
  status = esl_abc_GuessAlphabet(ct, &alphatype);


 DONE:
  esl_buffer_SetOffset(afp->bf, anchor);
  esl_buffer_RaiseAnchor(afp->bf, anchor);
  *ret_type = alphatype;
  return status;

 ERROR:
  if (anchor != -1) {
    esl_buffer_SetOffset(afp->bf, anchor);
    esl_buffer_RaiseAnchor(afp->bf, anchor);
  }
  *ret_type = eslUNKNOWN;
  return status;
}

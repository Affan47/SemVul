utest_FetchTokenAsStrWrapped(ESL_BUFFER *bf, int nlines_expected)
{
  char       msg[]  = "utest_FetchTokenAsStrWrapped() failed";
  const char sep[]  = " \t\r\n";
  int        nlines = 0;
  char      *tok;
  int        which;
  int        nc;
  esl_pos_t  n;
  int        status;

  while ((status = esl_buffer_FetchTokenAsStr(bf, sep, &tok, &n)) == eslOK)
    {
      nlines++;

      if (strlen(tok) != n)                                       esl_fatal(msg);
      if (*tok != '[')                                            esl_fatal(msg);
      if (! isdigit(*(tok+1)))                                    esl_fatal(msg);
      if (esl_mem_strtoi32(tok+1, n-1, 10, &nc, &which) != eslOK) esl_fatal(msg);
      if (nc    != n-1)                                           esl_fatal(msg);
      if      (which > nlines) nlines = which;
      else if (which < nlines)                                    esl_fatal(msg);
      free(tok);

      if (esl_buffer_FetchTokenAsStr(bf, sep, &tok, &n) != eslOK) esl_fatal(msg);
      if (strlen(tok) != n)                                       esl_fatal(msg);
      if (! isdigit(*tok))                                        esl_fatal(msg);
      if (esl_mem_strtoi32(tok, n, 10, &nc, &which)     != eslOK) esl_fatal(msg);
      if (nc    != n-1)                                           esl_fatal(msg);
      if (which != nlines)                                        esl_fatal(msg);
      if (*(tok+nc) != ']')                                       esl_fatal(msg);
      free(tok);
    }
  if (status != eslEOF)          esl_fatal(msg);
  if (nlines > nlines_expected)  esl_fatal(msg);
  return;
}

esl_strtok_adv(char **s, char *delim, char **ret_tok, int *opt_toklen, char *opt_endchar)
{
  char *end;
  char *tok    = *s;
  char  c      = '\0';
  int   n      = 0;
  int   status = eslEOL;

  tok += strspn(tok, delim);
  if (! *tok) tok = NULL;
  else
    {
      n    = strcspn(tok, delim);
      end  = tok + n;
      if (*end == '\0') *s = end;
      else
	{
	  c     = *end;
	  *end  = '\0';
	  *s    = end+1;
	}
      status = eslOK;
    }

  *ret_tok = tok;
  if (opt_toklen  != NULL) *opt_toklen  = n;
  if (opt_endchar != NULL) *opt_endchar = c;
  return status;
}

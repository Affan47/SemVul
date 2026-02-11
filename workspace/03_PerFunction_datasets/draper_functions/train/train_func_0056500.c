dequote_escapes (string)
     char *string;
{
  register char *s, *t, *s1;
  size_t slen;
  char *result, *send;
  int quote_spaces;
  DECLARE_MBSTATE;

  if (string == 0)
    return string;

  slen = strlen (string);
  send = string + slen;

  t = result = (char *)xmalloc (slen + 1);

  if (strchr (string, CTLESC) == 0)
    return (strcpy (result, string));

  quote_spaces = (ifs_value && *ifs_value == 0);

  s = string;
  while (*s)
    {
      if (*s == CTLESC && (s[1] == CTLESC || s[1] == CTLNUL || (quote_spaces && s[1] == ' ')))
	{
	  s++;
	  if (*s == '\0')
	    break;
	}
      COPY_CHAR_P (t, s, send);
    }
  *t = '\0';
  return result;
}

sh_backslash_quote_for_double_quotes (string)
     char *string;
{
  unsigned char c;
  char *result, *r, *s;

  result = (char *)xmalloc (2 * strlen (string) + 1);

  for (r = result, s = string; s && (c = *s); s++)
    {
      if (sh_syntaxtab[c] & CBSDQUOTE)
	*r++ = '\\';

      else if (c == CTLESC || c == CTLNUL)
	*r++ = CTLESC;

      *r++ = c;
    }

  *r = '\0';
  return (result);
}

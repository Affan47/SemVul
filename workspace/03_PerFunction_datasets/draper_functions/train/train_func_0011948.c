wordfree (wordexp_t *pwordexp)
{


  if (pwordexp && pwordexp->we_wordv)
    {
      char **wordv = pwordexp->we_wordv;

      for (wordv += pwordexp->we_offs; *wordv; ++wordv)
	free (*wordv);

      free (pwordexp->we_wordv);
      pwordexp->we_wordv = NULL;
    }
}

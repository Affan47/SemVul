uvwrite_perm_array (e, pzarg, zcmd, pccol)
     FILE *e;
     const char **pzarg;
     const char *zcmd;
     size_t *pccol;
{
  size_t c;
  const char **pz;

  if (pzarg == NULL)
    return;

  c = strlen (zcmd) + 1;

  for (pz = pzarg; *pz != NULL; pz++)
    c += strlen (*pz) + 1;

  if (*pccol > 20 && c + *pccol > 75)
    {
      fprintf (e, " \\\n");
      *pccol = c - 1;
    }
  else
    {
      if (*pccol != 0)
	fprintf (e, " ");
      *pccol += c;
    }

  fprintf (e, "%s=", zcmd);
  for (pz = pzarg; *pz != NULL; pz++)
    {
      if (pz != pzarg)
	fprintf (e, ":");
      fprintf (e, "%s", *pz);
    }
}

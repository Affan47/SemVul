prothypstates(long *k)
{

  boolean bottom;
  sitearray nothing;
  long i, n;
  seqptr hypset;

  fprintf(outfile, "\nFrom    To     Any Steps?    State at upper node\n");
  fprintf(outfile, "                             ");
  fprintf(outfile, "( . means same as in the node below it on tree)\n\n");
  memcpy(nothing, translate[(long)quest - (long)ala], sizeof(sitearray));
  hypset = (seqptr)Malloc(chars*sizeof(sitearray));
  for (i = 0; i < (chars); i++)
    memcpy(hypset[i], nothing, sizeof(sitearray));
  bottom = true;
  for (i = 1; i <= ((chars - 1) / 40 + 1); i++) {
    putc('\n', outfile);
    n = i * 40;
    if (n > chars)
      n = chars;
    bottom = true;
    prothyptrav(root, hypset, i * 40 - 39, n, k,&bottom,nothing);
  }
  free(hypset);
}

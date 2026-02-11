p7_domaindef_DumpPosteriors(FILE *ofp, P7_DOMAINDEF *ddef)
{
  int i;

  for (i = 1; i <= ddef->L; i++)
    fprintf(ofp, "%d %f\n", i, ddef->mocc[i]);
  fprintf(ofp, "&\n");

  for (i = 1; i <= ddef->L; i++)
    fprintf(ofp, "%d %f\n", i, ddef->btot[i]);
  fprintf(ofp, "&\n");

  for (i = 1; i <= ddef->L; i++)
    fprintf(ofp, "%d %f\n", i, ddef->etot[i]);
  fprintf(ofp, "&\n");

  for (i = 1; i <= ddef->L; i++)
    fprintf(ofp, "%d %f\n", i, ddef->n2sc[i]);
  fprintf(ofp, "&\n");

  return eslOK;
}

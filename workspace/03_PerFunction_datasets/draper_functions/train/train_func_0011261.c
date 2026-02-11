cro_gensumlineb(FILE *outf, Outchoices *od, int namecode, double x,
		     double x7, logical isaverage) {
  char *compsep = od->compsep;
  char *name = od->lngstr[namecode];

  if (isaverage)
    return;

  fprintf(outf, "x%s%c%c%s%.0f", compsep, name[0], name[1], compsep, x);

  if (x7 != UNSET)
    fprintf(outf, "\nx%s%c%c%s%.0f", compsep, name[2], name[3], compsep, x7);

  putc('\n', outf);
}

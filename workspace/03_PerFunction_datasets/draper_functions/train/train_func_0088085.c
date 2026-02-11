optimize_code4(FILE *lf)
{
  unsigned i;
  int changed = 0;

  for(i = 0; i < dict_size; i++) {
    if(
      i >= sizeof prim_names / sizeof *prim_names &&
      !dict[i].del &&
      !dict[i].ref &&
      !dict[i].def
    ) {
      if(verbose && lf) fprintf(lf, "#   unused: %s (index %d)\n", dict[i].name, i);

      dict[i].del = 1;

      changed = 1;
    }
  }

  return changed;
}

extract_word(int nr_fn, char **fns, FILE *ofp)
{
  struct string_pool sp;
  FILE *ifp;
  int i;

  string_pool_init(&sp);

  for (i = 0; i < nr_fn; i++) {
    ifp = fopen(fns[i], "r");
    if (!ifp) {
      fprintf(stderr, "failed to open (%s)\n", fns[i]);
      continue;
    }
    extract_word_from_file(ifp, &sp);
    fclose(ifp);
  }

  string_pool_sort(&sp);
  string_pool_dump(ofp, &sp);
}

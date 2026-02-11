print_tokens_gff3 (FILE *fp, List_T tokens) {
  List_T p;
  char *token;

  if (tokens != NULL) {
    p = tokens;
    token = (char *) List_head(p);
    fprintf(fp,"%s",token);

    for (p = List_next(p); p != NULL; p = List_next(p)) {
      token = (char *) List_head(p);
      fprintf(fp," %s",token);
    }
  }

  for (p = tokens; p != NULL; p = List_next(p)) {
    token = (char *) List_head(p);
    FREE(token);
  }

  return;
}

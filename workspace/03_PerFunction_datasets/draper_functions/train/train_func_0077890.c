get_vertex_num() {
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  regex_t * __restrict compiled_num = (regex_t *) malloc(sizeof (regex_t));
  (void) regcomp(compiled_num, "^p", REG_EXTENDED);
  char * dump = (char *) malloc(sizeof(char)*12);
  int vertex_num;
  int dump2;

  while ((read = getline(&line, &len, stdin)) != -1) {
    if (regexec(compiled_num, line, 0, NULL, 0) == 0) {
      sscanf(line,"%c %s %d %d", dump, dump,&vertex_num,&dump2);
      break;

    }
  }
  regfree(compiled_num);
  free(compiled_num);
  free(dump);
  if (line != NULL)
    free(line);
  return vertex_num;
}

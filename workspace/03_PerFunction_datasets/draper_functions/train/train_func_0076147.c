check_grammar_path(char *prefix)
{
  int i;

  i = strlen(prefix) - 1;
  while(prefix[i] != '.' && i >= 0) i--;
  if (i < 0 || strcmp(&(prefix[i]), ".dict") != 0) {
    snprintf(buf, MAXLINELEN, "%s.dfa", prefix);
    if (access(buf, R_OK) < 0) {
      fprintf(stderr, "Error: \"%s.dfa\" not exist\n", prefix);
      return -1;
    }
    snprintf(buf, MAXLINELEN, "%s.dict", prefix);
    if (access(buf, R_OK) < 0) {
      fprintf(stderr, "Error: \"%s.dict\" not exist\n", prefix);
      return -1;
    }
  } else {
    if (access(prefix, R_OK) < 0) {
      fprintf(stderr, "Error: \"%s\" not exist\n", prefix);
    }
  }
  return 0;
}

keyword(char *str) {
  int i;

  i = 0;

  while (scan_keywords[i].name != NULL) {
    if (!strcmp(str, scan_keywords[i].name))
      return scan_keywords[i].k;

    i++;
  }

  return -1;
}

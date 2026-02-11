init_term(char *filename, char **termname)
{
  FILE *fd;
  int n;
  static char buf[512];
  char *p;

  fprintf(stderr, "Reading in term file (optional)...");

  if ((fd = fopen_readfile(filename)) == NULL) {
    termname[0] = NULL;
    fprintf(stderr, "not found\n");
    return;
  }

  while (getl(buf, sizeof(buf), fd) != NULL) {
    if ((p = strtok(buf, DELM)) == NULL) {
      fprintf(stderr, "Error: term file failed to parse, corrupted or invalid data?\n");
      return;
    }
    n = atoi(p);
    if ((p = strtok(NULL, DELM)) == NULL) {
      fprintf(stderr, "Error: term file failed to parse, corrupted or invalid data?\n");
      return;
    }
    termname[n] = strdup(p);
  }
  if (fclose_readfile(fd) == -1) {
    fprintf(stderr, "close error\n");
    exit(1);
  }

  fprintf(stderr, "done\n");
}

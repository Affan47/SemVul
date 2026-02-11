print_revcomp (FILE *fp, char *nt, int len) {
  int i;

  for (i = len-1; i >= 0; --i) {
    fprintf(fp,"%c",complCode[(int) nt[i]]);
  }
  return;
}

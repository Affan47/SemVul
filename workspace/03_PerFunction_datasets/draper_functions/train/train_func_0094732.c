verbose_open(char open, const char *name)
{
  int l = strlen(name);
  if (verbose_pos && verbose_pos + 3 + l > 79) {
    fputc('\n', stderr);
    verbose_pos = 0;
  }
  if (verbose_pos) {
    fputc(' ', stderr);
    verbose_pos++;
  }
  fputc(open, stderr);
  fputs(name, stderr);
  verbose_pos += 1 + l;
}

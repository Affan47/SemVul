gt_xfgets(char *s, int size, FILE *stream)
{
  char *str;
  if ((str = fgets(s, size, stream)) == NULL) {
    if (ferror(stream)) {
      perror("cannot read string");
      exit(EXIT_FAILURE);
    }
  }
  return str;
}

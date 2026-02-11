read_stdin(char *s, int max) {
  int i = 0;

  while((check_stdin()) && (i < (max - 1)))
    s[i++] = fgetc(stdin);
  s[i] = '\0';
  return i;
}

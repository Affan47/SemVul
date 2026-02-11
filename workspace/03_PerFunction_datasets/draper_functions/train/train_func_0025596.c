skip_to_next(char ** sp, const char ch) {
  int steps;
  while (ch != 0 && (**sp) != ch) {
    (*sp)++;
    steps++;
  }
  if (ch != 0)
    (*sp)++;
  return (ch != 0 ? steps : -1);
}

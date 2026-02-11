sa_concat(char** x, char* y)
{
  int len = 0;
  if (x != NULL) {
    while (x[len] != NULL) {
      len++;
    }
  }
  if ((x = realloc(x, sizeof(char*) * (len + 2))) == NULL) {
    cmd_error("out of memory\n");
  }
  x[len++] = y;
  x[len++] = NULL;
  return x;
}

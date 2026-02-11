read_str (const char *input_str)
{
  static char input[128];
  int len;

  fputs (input_str, stderr);
  if (fgets (input, sizeof (input), stdin) == NULL)
    return NULL;

  len = strlen (input);
  if ((len > 0) && (input[len - 1] == '\n'))
    input[len - 1] = 0;
  if (input[0] == 0)
    return NULL;

  return input;
}

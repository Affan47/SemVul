get_newline (FILE * fp)
{
  gint c;

  c = fgetc (fp);
  while (c != EOF && c != '\n')
    c = fgetc (fp);
  return c;
}

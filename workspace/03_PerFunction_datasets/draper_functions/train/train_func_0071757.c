_skipspaces(f)
FILE *f;
{
  register int ch;

  do {
    ch = getc(f);
  } while (ch == ' ' || ch == '\t');
  if (ch != EOF)
    ungetc(ch, f);
  return f;
}

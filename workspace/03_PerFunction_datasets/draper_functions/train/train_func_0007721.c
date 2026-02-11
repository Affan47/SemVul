phase1_ungetc (int c)
{
  if (c != EOF)
    {
      if (c == '\n')
        --line_number;

      ungetc (c, fp);
    }
}

phase1_getc ()
{
  int c = getc (fp);

  if (c == EOF)
    {
      if (ferror (fp))
        error (EXIT_FAILURE, errno, _("error while reading \"%s\""),
               real_file_name);
      return EOF;
    }

  if (c == '\n')
    {
      line_number++;
      char_in_line = 0;
    }
  else
    char_in_line++;

  return c;
}

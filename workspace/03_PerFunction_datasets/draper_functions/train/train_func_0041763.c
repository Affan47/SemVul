LexerInput (char *buf, int max_size)
{
  if (file == NULL)
    return 0;

  if (!fgets (buf, max_size, file))
    {
      set_error ();
      return 0;
    }

  return strlen (buf);
}

ProcessResponseFile(const char *filename)
{
  int word_len = 0;
  int in_quote = 0;

  FILE *fp = fopen(filename, "rb");

  if (! fp)
    TextFatalError("Error: Cannot find RESPONSE file: %s\n", filename);


  word_buffer[0] = 0;

  for (;;)
  {
    int ch = fgetc(fp);

    if (ch == EOF)
      break;

    if (isspace(ch) && !in_quote)
    {
      if (word_len > 0)
        AddArg(word_buffer);

      word_len = 0;
      in_quote = 0;

      continue;
    }

    if (isspace(ch) && !in_quote)
      continue;

    if ((ch == '\n' || ch == '\r') && in_quote)
      break;

    if (ch == '"')
    {
      in_quote = ! in_quote;
      continue;
    }

    if (word_len >= MAX_WORD_LEN)
      TextFatalError("Error: option in RESPONSE file too long (limit %d chars)\n",
          MAX_WORD_LEN);

    word_buffer[word_len++] = ch;
    word_buffer[word_len] = 0;
  }

  if (in_quote)
    TextFatalError("Error: unclosed quotes in RESPONSE file\n");

  if (word_len > 0)
    AddArg(word_buffer);

  fclose(fp);
}

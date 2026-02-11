isTypedef(char *line)
{
  Tokenizer t(line);


  if (   (t.GetNextToken() == "typedef")
      && ((t.GetNextToken() != "struct") || (t.GetNextToken() != "{")) )
    {
    return true;
    }


  if (strncmp(line, "DECLARE_HANDLE(", 15) == 0)
    {
    return true;
    }

  return false;
}

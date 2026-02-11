EscapeQuotes(const char* str)
{
  std::string result = "";
  for(const char* ch = str; *ch != '\0'; ++ch)
    {
    if(*ch == '"')
      {
      result += '\\';
      }
    result += *ch;
    }
  return result;
}

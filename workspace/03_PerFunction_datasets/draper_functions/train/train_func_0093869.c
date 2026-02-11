unescapeString(char *line)
{
  std::string result;
  bool escaped = false;
  int index = 0;

  while (line[index] != 0 &&
         line[index] != gsmlib::CR && line[index] != gsmlib::LF)
  {
    if (escaped)
    {
      escaped = false;
      if (line[index] == 'r')
        result += gsmlib::CR;
      else if (line[index] == 'n')
        result += gsmlib::LF;
      else if (line[index] == '\\')
        result += '\\';
      else
        result += line[index];
    }
    else
      if (line[index] == '\\')
        escaped = true;
      else
        result += line[index];

    ++index;
  }
  return result;
}

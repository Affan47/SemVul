backslash(string const &str)
{
  string new_str = "";

  for(unsigned int i = 0; i < str.size(); i++)
  {
    if(str[i] == '\\')
    {
      new_str += str[i];
    }
    new_str += str[i];
  }

  return new_str;
}

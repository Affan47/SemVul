GetMSType(const char *str)
{
  if(!str) return MS_END;

  for(unsigned int i = 0; MSStrings[i] != 0; ++i)
    {
    if( strcmp(str, MSStrings[i]) == 0 )
      {
      return (MSType)i;
      }
    }


  CodeString codestring = str;
  std::string cs = codestring.GetAsString();
  for(unsigned int i = 0; MSStrings[i] != 0; ++i)
    {
    if( strcmp(cs.c_str(), MSStrings[i]) == 0 )
      {
      return (MSType)i;
      }
    }


  return MS_END;
}

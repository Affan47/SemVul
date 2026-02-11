trim( const string& s )
{
  if(s.length() == 0)
    return s;
  string::size_type b = s.find_first_not_of(" \t");
  string::size_type e = s.find_last_not_of(" \t");
  if(b == string::npos)
    return "";
  return string(s, b, e - b + 1);
}

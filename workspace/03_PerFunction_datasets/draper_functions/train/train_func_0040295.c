Capitalized(const kwsys_stl::string& s)
{
  kwsys_stl::string n;
  if(s.size() == 0)
    {
    return n;
    }
  n.resize(s.size());
  n[0] = static_cast<kwsys_stl::string::value_type>(toupper(s[0]));
  for (size_t i = 1; i < s.size(); i++)
    {
    n[i] = static_cast<kwsys_stl::string::value_type>(tolower(s[i]));
    }
  return n;
}

isAuthorizedDN(const std::string str)
{
  bool res = false;
  for( std::vector<std::string>::const_iterator i=authDnList.begin(); i!=authDnList.end() && !res; i++)
    res = (*i == str);
  return res;
}

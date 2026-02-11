createTransmission(const std::string& str)
{
  std::string result;
  std::istringstream is(str);
  while (is) {
    std::string s;
    is >> s;
    if (s.empty())
      break;
    std::string::iterator si = s.begin();
    for (; si != s.end(); si++)
      *si = toupper(*si);
    result.append(s);
  }
  if (result.substr(0,4) == "IBAN")
    result = result.substr(4);
  return result;
}

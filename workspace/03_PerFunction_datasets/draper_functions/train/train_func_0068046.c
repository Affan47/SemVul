replace(string & s, const string & s1, const string & s2, const char skip)
{
  string::size_type pos = 0;
  while (1) {
    string::size_type i = s.find(s1, pos);
    if (i == string::npos) break;
    if (i > 0 && s[i-1] == skip) {
      pos = i + 1;
      continue;
    }
    s.replace(i, s1.size(), s2);
    pos = i + s2.size();
  }

}

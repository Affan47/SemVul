tokenize(vector<string>& dst, const string& buf,
    const string& sep, bool coalesce)
{
  string::size_type s = 0;
  string::size_type e = buf.find_first_of(sep, s);

  while(s != string::npos || e != string::npos)
  {
    if(e != string::npos)
      dst.push_back(buf.substr(s, e - s));
    else
    {
      dst.push_back(buf.substr(s));
      break;
    }

    if(coalesce)
      s = buf.find_first_not_of(sep, e);
    else
      s = e + 1;

    e = buf.find_first_of(sep, s);
  }

  return dst;
}

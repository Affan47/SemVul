split(char c, string s, list<string> & r)
{
  size_t b=0, e;
  e=s.find(c,b);
  if (e<s.npos)
    {
      do
        {
          r.push_back(s.substr(b,e-b));
          b=e+1;
          e=s.find(c,b);
        }
      while (e<s.npos);
      if (b<s.length())
        r.push_back(s.substr(b,e-b));
    }
  else
    r.push_back(s);
}

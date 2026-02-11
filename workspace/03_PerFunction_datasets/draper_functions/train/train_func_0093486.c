kvu_convert_to_lowercase(const string& a)
{
  string r = a;
  for(string::iterator p = r.begin(); p != r.end(); p++)
    *p = tolower(*p);
  return r;
}

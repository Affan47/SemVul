kvu_to_uppercase(string& a)
{
  string::iterator p = a.begin();
  while(p != a.end()) {
    *p = toupper(*p);
    ++p;
  }
}

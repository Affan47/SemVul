isstring(string s)
{
  if (s.size()<2) return false;
  if (s[0]!='\"' || s[(int)s.size()-1]!='\"') return false;

  for (int i=1;i<(int)s.size()-1;i++) {
    if (s[i]=='\"') return false;
  }
  return true;
}

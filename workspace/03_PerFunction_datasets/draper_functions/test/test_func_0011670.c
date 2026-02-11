str_count(const str* s, char ch)
{
  int pos;
  unsigned count;

  count = 0;
  for (pos = str_findfirst(s, ch); pos >= 0;
       pos = str_findnext(s, ch, pos+1))
    ++count;
  return count;
}

etrans2string() const
{
  basic_string<char> s;
  if (null()) return s;
  s.append (src().estate2string());
  s.append ("=>");
  s.append (dest().estate2string());
  s.append (" (");
  for (int n = 0; n < nodes(); ++n)
    {
      if (n > 0)
	s.append (", ");
      s.append (tpath[n].tpath2string());
    }
  s.append (")");
  return s;
}

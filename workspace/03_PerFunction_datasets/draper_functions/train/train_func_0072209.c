substr(int pos, int len) const
{
  int s = size();

  if (pos < 0)
    pos = 0;
  else if (pos >= s)
    pos = s;
  if (len < 0)
    len = s;
  if (pos + len >= s)
    len = s - pos;

  if (pos == 0 && len == s)
    return *this;

  return UString(Rep::create(m_rep, pos, len));
}

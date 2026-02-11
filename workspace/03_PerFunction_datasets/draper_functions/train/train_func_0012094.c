capitalize(QString s)
{
  s = s.toLower();
  if (s.size() > 0)
    s[0] = s[0].toUpper();
  return s;
}

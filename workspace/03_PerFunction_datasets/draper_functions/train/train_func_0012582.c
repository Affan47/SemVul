prefix(const QString& s)
{
  QString prefix = s.section('_', 0, 0);
  if(prefix == s)
    {
    prefix = QString();
    }
  return prefix;
}

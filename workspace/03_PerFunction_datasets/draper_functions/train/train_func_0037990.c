traceKey()
{
  if (!_data || _data->command().isEmpty()) return QString();

  QString name = _data->command();
  QString key;
  for (int l=0;l<name.length();l++)
    if (name[l].isLetterOrNumber()) key += name[l];

  return QString("-") + key;
}

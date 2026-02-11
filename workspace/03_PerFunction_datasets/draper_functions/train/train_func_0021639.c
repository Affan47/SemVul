setFunction(const QString &n, const QString &className = QString())
{
  QString result = QString::fromLatin1("set") + n;
  result[3] = result[3].toUpper();

  if ( !className.isEmpty() )
    result = className + QString::fromLatin1("::") + result;
  return result;
}

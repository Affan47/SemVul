literalString( const QString &s )
{
  bool isAscii = true;
  for(int i = s.length(); i--;)
     if (s[i].unicode() > 127) isAscii = false;

  if (isAscii)
     return QString::fromLatin1("QLatin1String( ") + quoteString(s) + QString::fromLatin1(" )");
  else
     return QString::fromLatin1("QString::fromUtf8( ") + quoteString(s) + QString::fromLatin1(" )");
}

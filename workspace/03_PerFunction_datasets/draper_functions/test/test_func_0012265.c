prettyUrl( AdjustPathOption trailing ) const
{


  QString result = scheme();
  if (!result.isEmpty())
  {
    if (!authority().isEmpty() || result == QLatin1String("file") || path().isEmpty())
        result += QLatin1String("://");
    else
        result += QLatin1Char(':');
  }

  QString tmp = userName();
  if (!tmp.isEmpty()) {
    result += QString::fromLatin1(QUrl::toPercentEncoding(tmp));
    result += QLatin1Char('@');
  }


  tmp = host();
  if (tmp.contains(QLatin1Char(':')))
    result += QLatin1Char('[') + tmp + QLatin1Char(']');
  else
    result += tmp;

  if (port() != -1) {
    result += QLatin1Char(':');
    result += QString::number(port());
  }

  tmp = path();
#ifdef Q_WS_WIN
  if (isLocalFile())
    tmp.prepend(QLatin1Char('/'));
#endif
  result += toPrettyPercentEncoding(tmp, false);


  if (trailing == AddTrailingSlash && !tmp.endsWith(QLatin1Char('/')))
    result += QLatin1Char('/');
  else if (trailing == RemoveTrailingSlash && tmp.length() > 1 && tmp.endsWith(QLatin1Char('/')))
    result.chop(1);

  if (hasQuery()) {
    result += QLatin1Char('?');
    result += QString::fromLatin1(encodedQuery());
  }

  if (hasFragment()) {
    result += QLatin1Char('#');
    result += toPrettyPercentEncoding(fragment(), true);
  }

  return result;
}

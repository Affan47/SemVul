validate ( QString &str, int & ) const
{
  bool ok;
  int  val = 0;
  QString newStr;

  newStr = str.trimmed();
  if (d->_base > 10)
    newStr = newStr.toUpper();

  if (newStr == QLatin1String("-")) {
    if ((d->_min || d->_max) && d->_min >= 0)
      ok = false;
    else
      return QValidator::Acceptable;
  }
  else if (!newStr.isEmpty())
    val = newStr.toInt(&ok, d->_base);
  else {
    val = 0;
    ok = true;
  }

  if (! ok)
    return QValidator::Invalid;

  if ((! d->_min && ! d->_max) || (val >= d->_min && val <= d->_max))
    return QValidator::Acceptable;

  if (d->_max && d->_min >= 0 && val < 0)
    return QValidator::Invalid;

  return QValidator::Intermediate;
}

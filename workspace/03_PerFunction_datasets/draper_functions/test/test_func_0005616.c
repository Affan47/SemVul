tolower(string const &str) const
{
  return UtfConverter::toUtf8(StringUtils::tolower(UtfConverter::fromUtf8(str)));
}

proxied_handler_name(const String &n) const
{
  if (_full_proxy && find(n, '.') == n.end())
    return "0." + n;
  else
    return n;
}

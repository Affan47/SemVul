getStringOrNull(DOM::DOMString s)
{
  if (s.isNull())
    return jsNull();
  else
    return jsString(s);
}

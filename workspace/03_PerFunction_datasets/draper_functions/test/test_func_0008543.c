my_xml_entity_to_char(const char *name, uint length)
{
  if (length == 2)
  {
    if (!memcmp(name, "gt", length))
      return '>';
    if (!memcmp(name, "lt", length))
      return '<';
  }
  else if (length == 3)
  {
    if (!memcmp(name, "amp", length))
      return '&';
  }
  else if (length == 4)
  {
    if (!memcmp(name, "quot", length))
      return '"';
    if (!memcmp(name, "apos", length))
      return '\'';
  }
  return -1;
}

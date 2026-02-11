parseToTag()
{
  for (;;) {
    String s = parseToTagX();
    if (s.size() < 3 ||
	(s[0] != '/' && (s[0] != 'x' || s[1] != '-')) ||
	(s[0] == '/' && (s[1] != 'x' || s[2] != '-')))
      return s;
    if (s[0] != '/') {
      XmlAttributes attr;
      if (!parseAttributes(attr))
	return String();
    }
  }
}

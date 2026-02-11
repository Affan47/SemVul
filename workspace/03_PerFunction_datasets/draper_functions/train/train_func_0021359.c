parseAttributes(XmlAttributes &attr, bool qm)
{

  attr.clear();
  skipWhitespace();
  while (iCh != '>' && iCh != '/' && iCh != '?') {
    String attname;
    while (isTagChar(iCh)) {
      attname += char(iCh);
      getChar();
    }

    skipWhitespace();
    if (attname.empty() || iCh != '=')
      return false;
    getChar();
    skipWhitespace();

    int quote = iCh;
    if (iCh != '\"' && iCh != '\'')
      return false;
    getChar();
    String val;
    while (!eos() && iCh != quote) {
      val += char(iCh);
      getChar();
    }
    if (iCh != quote)
      return false;
    getChar();
    skipWhitespace();
    attr.add(attname, fromXml(val));
  }

  if (iCh == '/' || (qm && iCh == '?')) {
    attr.setSlash();
    getChar();
    skipWhitespace();
  }

  if (iCh != '>')
    return false;
  getChar();
  return true;
}

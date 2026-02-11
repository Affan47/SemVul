stripName(FixString& s)
{
    if (_len==0) return false;


    if (!QChar(*_str).isLetter() && (*_str != '_')) return false;

    int newLen = 1;
    const char* newStr = _str;

    _str++;
    _len--;

    while(_len>0) {
      if (!QChar(*_str).isLetterOrNumber()
	  && (*_str != '_')) break;

      newLen++;
      _str++;
      _len--;
    }

    s.set(newStr, newLen);
    return true;
}

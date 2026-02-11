pad(string s, int width, TextTable::Align align)
{
  int lpad, rpad;
  lpad = rpad = 0;
  switch (align) {
    case TextTable::LEFT:
      rpad = width - s.length();
      break;
    case TextTable::CENTER:
      lpad = width / 2 - s.length() / 2;
      rpad = width - lpad - s.length();
      break;
    case TextTable::RIGHT:
      lpad = width - s.length();
      break;
  }

  return string(lpad, ' ') + s + string(rpad, ' ');
}

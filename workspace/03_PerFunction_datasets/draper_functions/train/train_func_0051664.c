append(const UString& inStr, bool quote)
{
  if (quote)
    *this << '"';
  const UTF16* src = &inStr.data()->uc;
  const size_t size = inStr.size();
  for (size_t i = 0; i < size; ++i) {
    if (bufUsed >= kBufSize - 8)
      flush();
    UTF16 c = *src++, esc = '\\';
    switch (c) {
      case '\"':                break;
      case '\n':    c = 'n';    break;
      case '\r':    c = 'r';    break;
      case '\t':    c = 't';    break;
      case '\\':                break;
      default:
        if (c >= 128 || !isprint(c)) {
          char hexValue[8];
          int len = sprintf(hexValue, (c < 256) ? "\\x%02X" : "\\u%04X", c);
          UTF16* dst = &buffer[bufUsed];
          bufUsed += len;
          for (int j = 0; j < len; ++j)
            dst[j] = hexValue[j];
          continue;
        }
        esc = 0;
        break;
    }
    if (esc) put(esc);
    put(c);
  }

  if (quote)
    *this << '"';
  return *this;
}

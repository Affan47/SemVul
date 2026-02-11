from(int i)
{
  UChar buf[1 + sizeof(i) * 3];
  UChar *end = buf + sizeof(buf) / sizeof(UChar);
  UChar *p = end;

  if (i == 0) {
    *--p = '0';
  } else if (i == INT_MIN) {
    char minBuf[1 + sizeof(i) * 3];
    sprintf(minBuf, "%d", INT_MIN);
    return UString(minBuf);
  } else {
    bool negative = false;
    if (i < 0) {
      negative = true;
      i = -i;
    }
    while (i) {
      *--p = (unsigned short)((i % 10) + '0');
      i /= 10;
    }
    if (negative) {
      *--p = '-';
    }
  }

  return UString(p, static_cast<int>(end - p));
}

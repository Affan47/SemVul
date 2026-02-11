fc_url_encode(const char *txt)
{
  static char buf[2048];
  unsigned ch;
  char *ptr;


  if (sizeof(buf) <= (3*strlen(txt))) {
    return "";
  }

  for (ptr = buf; *txt != '\0'; txt++) {
    ch = (unsigned char) *txt;

    if (is_url_safe(ch)) {
      *ptr++ = *txt;
    } else if (ch == ' ') {
      *ptr++ = '+';
    } else {
      sprintf(ptr, "%%%2.2X", ch);
      ptr += 3;
    }
  }
  *ptr++ = '\0';

  return buf;
}

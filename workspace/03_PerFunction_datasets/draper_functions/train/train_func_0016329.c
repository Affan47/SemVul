pax25(char *buf, const unsigned char *data)
{
  int i, ssid;
  char *s;
  char c;

  s = buf;

  for (i = 0; i < ALEN; i++) {
    c = (data[i] >> 1) & 0x7F;

    if (!isalnum(c) && c != ' ') {
      strcpy(buf, "[invalid]");
      return buf;
    }

    if (c != ' ') *s++ = c;
  }

  if ((ssid = (data[ALEN] & SSID)>>1) != 0)
    sprintf(s, "-%d", ssid);
  else
    *s = '\0';

  return(buf);
}

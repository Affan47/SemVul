scsi_fixstring(unsigned char *s, int bytecount)
{
  unsigned char *p;
  unsigned char *end;

  p = s;
  end = s + bytecount;


  while (s != end && *s == ' ')
    ++s;

  while (s != end && *s) {
    if (*s++ != ' ' || (s != end && *s && *s != ' '))
      *p++ = *(s-1);
  }

  while (p != end)
    *p++ = '\0';
}

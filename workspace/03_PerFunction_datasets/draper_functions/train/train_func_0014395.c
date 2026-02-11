de_escape(char *s, int wide)
{
  int src = 0;
  int dst = 0;

  if (wide) {
    while ( *(s + src) || *(s + src +1)) {
      if ( *(s + src) == '\\' && *(s + src + 1) == 0) src += 2;
      *(s + dst) = *(s + src);
      *(s + dst + 1) = *(s + src + 1);
      dst += 2;
      src += 2;
    }
    *(s + dst) = 0;
    *(s + dst + 1) = 0;
    dst += 2;
  } else {
    while ( *(s + src) ) {
      if ( *(s + src) == '\\' ) src++;
      *(s + dst) = *(s + src);
      dst++;
      src++;
    }
    *(s + dst) = 0;
    dst++;
  }

  return(dst);
}

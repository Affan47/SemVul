my_valid_mbcharlen_utf8mb4(CHARSET_INFO *cs __attribute__((unused)),
                           const uchar *s, const uchar *e)
{
  uchar c;

  if (s >= e)
    return MY_CS_TOOSMALL;

  c= s[0];
  if (c < 0xf0)
    return my_valid_mbcharlen_utf8mb3(s, e);

  if (c < 0xf5)
  {
    if (s + 4 > e)
      return MY_CS_TOOSMALL4;


    if (!(IS_CONTINUATION_BYTE(s[1]) &&
          IS_CONTINUATION_BYTE(s[2]) &&
          IS_CONTINUATION_BYTE(s[3]) &&
          (c >= 0xf1 || s[1] >= 0x90) &&
          (c <= 0xf3 || s[1] <= 0x8F)))
      return MY_CS_ILSEQ;

    return 4;
  }

  return MY_CS_ILSEQ;
}

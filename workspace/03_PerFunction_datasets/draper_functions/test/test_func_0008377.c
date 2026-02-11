my_mbcharlen_utf8(CHARSET_INFO *cs  __attribute__((unused)),
                              uint c)
{
  if (c < 0x80)
    return 1;
  else if (c < 0xc2)
    return 0;
  else if (c < 0xe0)
    return 2;
  else if (c < 0xf0)
    return 3;
#ifdef UNICODE_32BIT
  else if (c < 0xf8)
    return 4;
  else if (c < 0xfc)
    return 5;
  else if (c < 0xfe)
    return 6;
#endif
  return 0; ;
}

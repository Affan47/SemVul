utf162utf8 (ACEXML_UTF16 src,
                               ACEXML_UTF8 *dst,
                               size_t len)
{


  if (dst == 0)
    return ACEXML_INVALID_ARGS;

  if (src < 0x80)
    {
      if (len < 1)
        return ACEXML_DESTINATION_TOO_SHORT;

      *dst = static_cast<ACEXML_UTF8> (src);
      return 1;
    }
  else if (src < 0x800)
    {
      if (len < 2)
        return ACEXML_DESTINATION_TOO_SHORT;

      *dst = 0xc0 | (static_cast<ACEXML_UTF8> (src) / 0x40);
      *(dst+1) = 0x80 | (static_cast<ACEXML_UTF8> (src) % 0x40);
      return 2;
    }
  else
    {
      if (len < 3)
        return ACEXML_DESTINATION_TOO_SHORT;


      if (src >= 0xD800 && src < 0xE000)
        return ACEXML_IS_SURROGATE;

      *dst = 0xe0 | (static_cast<ACEXML_UTF8> (src) / 0x1000);
      *(dst+1) = 0x80 | ((static_cast<ACEXML_UTF8> (src) % 0x1000) / 0x40);
      *(dst+2) = 0x80 | (static_cast<ACEXML_UTF8> (src) % 0x40);
      return 3;
    }
}

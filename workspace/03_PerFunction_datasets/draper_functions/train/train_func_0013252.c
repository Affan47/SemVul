shift_jis_character_iterator (const char *s)
{
  unsigned char c = *s;
  if ((c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xf9))
    {
      unsigned char c2 = s[1];
      if ((c2 >= 0x40 && c2 <= 0x7e) || (c2 >= 0x80 && c2 <= 0xfc))
        return 2;
    }
  return 1;
}

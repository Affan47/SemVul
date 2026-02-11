utf8_character_iterator (const char *s)
{
  unsigned char c = *s;
  if (c >= 0xc2)
    {
      if (c < 0xe0)
        {
          unsigned char c2 = s[1];
          if (c2 >= 0x80 && c2 < 0xc0)
            return 2;
        }
      else if (c < 0xf0)
        {
          unsigned char c2 = s[1];
          if (c2 >= 0x80 && c2 < 0xc0)
            {
              unsigned char c3 = s[2];
              if (c3 >= 0x80 && c3 < 0xc0)
                return 3;
            }
        }
      else if (c < 0xf8)
        {
          unsigned char c2 = s[1];
          if (c2 >= 0x80 && c2 < 0xc0)
            {
              unsigned char c3 = s[2];
              if (c3 >= 0x80 && c3 < 0xc0)
                {
                  unsigned char c4 = s[3];
                  if (c4 >= 0x80 && c4 < 0xc0)
                    return 4;
                }
            }
        }
    }
  return 1;
}

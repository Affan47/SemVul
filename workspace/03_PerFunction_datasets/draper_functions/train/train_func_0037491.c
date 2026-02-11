u8_prev (ucs4_t *puc, const uint8_t *s, const uint8_t *start)
{

  if (s != start)
    {
      uint8_t c_1 = s[-1];

      if (c_1 < 0x80)
        {
          *puc = c_1;
          return s - 1;
        }
#if CONFIG_UNICODE_SAFETY
      if ((c_1 ^ 0x80) < 0x40)
#endif
        if (s - 1 != start)
          {
            uint8_t c_2 = s[-2];

            if (c_2 >= 0xc2 && c_2 < 0xe0)
              {
                *puc = ((unsigned int) (c_2 & 0x1f) << 6)
                       | (unsigned int) (c_1 ^ 0x80);
                return s - 2;
              }
#if CONFIG_UNICODE_SAFETY
            if ((c_2 ^ 0x80) < 0x40)
#endif
              if (s - 2 != start)
                {
                  uint8_t c_3 = s[-3];

                  if (c_3 >= 0xe0 && c_3 < 0xf0
#if CONFIG_UNICODE_SAFETY
                      && (c_3 >= 0xe1 || c_2 >= 0xa0)
                      && (c_3 != 0xed || c_2 < 0xa0)
#endif
                     )
                    {
                      *puc = ((unsigned int) (c_3 & 0x0f) << 12)
                             | ((unsigned int) (c_2 ^ 0x80) << 6)
                             | (unsigned int) (c_1 ^ 0x80);
                      return s - 3;
                    }
#if CONFIG_UNICODE_SAFETY
                  if ((c_3 ^ 0x80) < 0x40)
#endif
                    if (s - 3 != start)
                      {
                        uint8_t c_4 = s[-4];

                        if (c_4 >= 0xf0 && c_4 < 0xf8
#if CONFIG_UNICODE_SAFETY
                            && (c_4 >= 0xf1 || c_3 >= 0x90)
                            && (c_4 < 0xf4 || (c_4 == 0xf4 && c_3 < 0x90))
#endif
                           )
                          {
                            *puc = ((unsigned int) (c_4 & 0x07) << 18)
                                   | ((unsigned int) (c_3 ^ 0x80) << 12)
                                   | ((unsigned int) (c_2 ^ 0x80) << 6)
                                   | (unsigned int) (c_1 ^ 0x80);
                            return s - 4;
                          }
                      }
                }
          }
    }
  return NULL;
}

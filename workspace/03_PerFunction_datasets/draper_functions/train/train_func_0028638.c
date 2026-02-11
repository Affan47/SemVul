cet_utf8_to_ucs4(const char* str, int* bytes, int* value)
{
  unsigned char* cp = (unsigned char*)str;

  if (*cp < 0x80) {
    if (bytes != NULL) {
      *bytes = 1;
    }
    if (value != NULL) {
      *value = *cp;
    }
    return CET_SUCCESS;
  } else {
    unsigned char bits = 0xc0;
    unsigned char mask = 0xe0;
    int len = 0;

    for (len = 1; len <= 6; len++) {
      if ((*cp & mask) == bits) {
        int i = len;
        while (i-- > 0) {
          cp++;
          if ((*cp & 0xc0) != 0x80) {
            break;
          } else if (i == 0) {
            char* c = (char*)str;
            int res = *c++ & (mask ^ 0xFF);
            i = len;
            while (i-- > 0) {
              res = (res << 6) | (*c++ & 0x3f);
            }

            if (bytes != NULL) {
              *bytes = len + 1;
            }
            if (value != NULL) {
              *value = res;
            }
            return CET_SUCCESS;
          }
        }
      }
      bits = (bits >> 1) | 0x80;
      mask = (mask >> 1) | 0x80;
    }
  }
  if (bytes != NULL) {
    *bytes = 1;
  }
  if (value != NULL) {
    *value = *cp;
  }
  return CET_ERROR;
}

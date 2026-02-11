parse_ipv4_addr(const char *s, in_addr_t *addr, char **endptr)
{
  const char *p = s;
  uint8_t buf[sizeof *addr];
  uint8_t *a = addr ? (uint8_t *) addr : buf;
  bool is_valid = true;
  int i, j, v;

  for (i = 0; i < 4; i++) {
    v = 0;
    for (j = 0; j < 3; j++) {
      if (*p < '0' || *p > '9') {
        is_valid = j > 0;
        break;
      }
      v *= 10;
      v += *p++ - '0';
    }
    if (!is_valid)
      break;
    if (i < 3) {
      if (*p != '.') {
        is_valid = false;
        break;
      }
      p++;
    }
    *a++ = (uint8_t) v;
  }

  if (endptr)
    *endptr = deconstify_char_ptr(p);

  if (!is_valid) {
    if (addr)
      *addr = 0;
    return false;
  }
  return true;
}

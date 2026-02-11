obstcp_advert_cname_extract(char *output, unsigned *ooutlen, const char *name) {
  unsigned j = 0;
  const unsigned outlen = *ooutlen;

  while (*name) {
    if (strncmp(name, kDNSMagic, kDNSMagicLen) == 0) {
      char good = 1;
      unsigned count = 0;
      const char *i;

      for (i = name + kDNSMagicLen; *i; ++i, count++) {
        const char c = *i;
        if (c == '.' || !c)
          break;
        if ((c >= '0' && c <= '9') ||
          (c > 'a' && c <= 'z' && c != 'e' && c != 'i' && c != 'o') ||
          (c > 'A' && c <= 'Z' && c != 'E' && c != 'I' && c != 'O'))
          continue;
        good = 0;
        break;
      }

      if (!count)
        good = 0;

      if (good) {
        if (!buffer_put((uint8_t *) output, outlen, &j,
                        name + kDNSMagicLen, count)) goto spc;
        name += kDNSMagicLen + count;
        if (*name == '.')
          name++;
        continue;
      }
    }

    while (*name && *name != '.')
      name++;
    if (*name == '.') {
      name++;
    } else {
      break;
    }
  }

  if (!j) {
    errno = EEXIST;
    return 0;
  }

  *ooutlen = j;

  return 1;

 spc:
  errno = ENOSPC;
  return 0;
}

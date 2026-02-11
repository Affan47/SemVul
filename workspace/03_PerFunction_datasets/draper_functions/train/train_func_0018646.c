tor_addr_to_PTR_name(char *out, size_t outlen,
                     const tor_addr_t *addr)
{
  tor_assert(out);
  tor_assert(addr);

  if (addr->family == AF_INET) {
    uint32_t a = tor_addr_to_ipv4h(addr);

    return tor_snprintf(out, outlen, "%d.%d.%d.%d.in-addr.arpa",
                        (int)(uint8_t)((a    )&0xff),
                        (int)(uint8_t)((a>>8 )&0xff),
                        (int)(uint8_t)((a>>16)&0xff),
                        (int)(uint8_t)((a>>24)&0xff));
  } else if (addr->family == AF_INET6) {
    int i;
    char *cp = out;
    const uint8_t *bytes = tor_addr_to_in6_addr8(addr);
    if (outlen < REVERSE_LOOKUP_NAME_BUF_LEN)
      return -1;
    for (i = 15; i >= 0; --i) {
      uint8_t byte = bytes[i];
      *cp++ = "0123456789abcdef"[byte & 0x0f];
      *cp++ = '.';
      *cp++ = "0123456789abcdef"[byte >> 4];
      *cp++ = '.';
    }
    memcpy(cp, "ip6.arpa", 9);
    return 32 * 2 + 8;
  }
  return -1;
}

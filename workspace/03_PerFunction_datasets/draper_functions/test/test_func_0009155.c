ssh_get_hexa(const unsigned char *what, size_t len) {
  const char h[] = "0123456789abcdef";
  char *hexa;
  size_t i;
  size_t hlen = len * 3;

  if (len > (UINT_MAX - 1) / 3) {
    return NULL;
  }

  hexa = malloc(hlen + 1);
  if (hexa == NULL) {
    return NULL;
  }

  for (i = 0; i < len; i++) {
      hexa[i * 3] = h[(what[i] >> 4) & 0xF];
      hexa[i * 3 + 1] = h[what[i] & 0xF];
      hexa[i * 3 + 2] = ':';
  }
  hexa[hlen - 1] = '\0';

  return hexa;
}

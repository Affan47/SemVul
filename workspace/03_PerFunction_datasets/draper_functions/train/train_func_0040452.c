key_keyid(const uint8_t *key) {
  uint32_t keyid = 0;
  unsigned i;

  for (i = 0; i < 8; ++i) {
    keyid ^= ((const uint32_t *) key)[i];
  }

  return keyid;
}

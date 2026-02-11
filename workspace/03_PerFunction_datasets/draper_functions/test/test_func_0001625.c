memcmp(const void *s1, const void *s2, size_t n) {
  size_t i;
  uint8_t* sr1 = (uint8_t*)s1;
  uint8_t* sr2 = (uint8_t*)s2;

  for(i = 0; i < n; ++i) {
    if(sr1[i] != sr2[i]) {
      return sr1[i] - sr2[i];
    }
  }

  return 0;
}

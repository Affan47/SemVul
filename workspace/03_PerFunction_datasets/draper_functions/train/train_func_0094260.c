crypto_aead_encrypt(
    unsigned char *c, unsigned long long *clen,
    const unsigned char *m, unsigned long long mlen,
    const unsigned char *ad, unsigned long long adlen,
    const unsigned char *nsec,
    const unsigned char *npub,
    const unsigned char *k) {

  u64 K0 = U64BIG(((u64*)k)[0]);
  u64 K1 = U64BIG(((u64*)k)[1]);
  u64 N0 = U64BIG(((u64*)npub)[0]);
  u64 N1 = U64BIG(((u64*)npub)[1]);
  u64 x0, x1, x2, x3, x4;
  u64 t0, t1, t2, t3, t4;
  u64 rlen;
  int i;


  x0 = (u64)((CRYPTO_KEYBYTES * 8) << 16 | PA_ROUNDS << 8 | PB_ROUNDS << 0) << 40;
  x1 = K0;
  x2 = K1;
  x3 = N0;
  x4 = N1;
  P12;
  x3 ^= K0;
  x4 ^= K1;


  if (adlen) {
    rlen = adlen;
    while (rlen >= RATE) {
      x0 ^= U64BIG(*(u64*)ad);
      P6;
      rlen -= RATE;
      ad += RATE;
    }
    for (i = 0; i < rlen; ++i, ++ad)
      x0 ^= INS_BYTE(*ad, i);
    x0 ^= INS_BYTE(0x80, rlen);
    P6;
  }
  x4 ^= 1;


  rlen = mlen;
  while (rlen >= RATE) {
    x0 ^= U64BIG(*(u64*)m);
    *(u64*)c = U64BIG(x0);
    P6;
    rlen -= RATE;
    m += RATE;
    c += RATE;
  }
  for (i = 0; i < rlen; ++i, ++m, ++c) {
    x0 ^= INS_BYTE(*m, i);
    *c = EXT_BYTE(x0, i);
  }
  x0 ^= INS_BYTE(0x80, rlen);


  x1 ^= K0;
  x2 ^= K1;
  P12;
  x3 ^= K0;
  x4 ^= K1;


  ((u64*)c)[0] = U64BIG(x3);
  ((u64*)c)[1] = U64BIG(x4);
  *clen = mlen + CRYPTO_KEYBYTES;

  return 0;
}

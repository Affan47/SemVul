encrypt(char* buf, int n, U64 offset) {
  for (U64 i=offset/16; i<=(offset+n)/16; ++i) {
    unsigned char ct[16];
    encrypt(iv0, iv1, i>>32, i, ct);
    for (int j=0; j<16; ++j) {
      const int k=i*16-offset+j;
      if (k>=0 && k<n)
        buf[k]^=ct[j];
    }
  }
}

tweak_expand(v16qi T[16], v16qi K[16], v16qi T3[48]) {
  int i;

  for (i = 0; i<16; i++)
    T3[i] = T[i];

  for (i = 0; i<8; i++) {
    T3[16+key_idx(i)]   = T[key_idx(i)] ^ T[key_idx(i+8)];
    T3[16+key_idx(i+8)] = T[key_idx(i)];
    T3[32+key_idx(i)]   = T[key_idx(i+8)];
    T3[32+key_idx(i+8)] = T[key_idx(i)] ^ T[key_idx(i+8)];
  }

  for (i = 0; i<48; i++)
    T3[i] ^= K[i%16];
}

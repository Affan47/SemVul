galois_shift_multiply(int x, int y, int w)
{
  int prod;
  int i, j, ind;
  int k;
  int scratch[33];

  prod = 0;
  for (i = 0; i < w; i++) {
    scratch[i] = y;
    if (y & (1 << (w-1))) {
      y = y << 1;
      y = (y ^ prim_poly[w]) & nwm1[w];
    } else {
      y = y << 1;
    }
  }
  for (i = 0; i < w; i++) {
    ind = (1 << i);
    if (ind & x) {
      j = 1;
      for (k = 0; k < w; k++) {
        prod = prod ^ (j & scratch[i]);
        j = (j << 1);
      }
    }
  }
  return prod;
}

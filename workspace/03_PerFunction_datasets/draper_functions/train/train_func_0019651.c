ss_inplacemerge(const sauchar_t *T, const saidx_t *PA,
                saidx_t *first, saidx_t *middle, saidx_t *last,
                saidx_t depth) {
  const saidx_t *p;
  saidx_t *a, *b;
  saidx_t len, half;
  saint_t q, r;
  saint_t x;

  for(;;) {
    if(*(last - 1) < 0) { x = 1; p = PA + ~*(last - 1); }
    else                { x = 0; p = PA +  *(last - 1); }
    for(a = first, len = middle - first, half = len >> 1, r = -1;
        0 < len;
        len = half, half >>= 1) {
      b = a + half;
      q = ss_compare(T, PA + ((0 <= *b) ? *b : ~*b), p, depth);
      if(q < 0) {
        a = b + 1;
        half -= (len & 1) ^ 1;
      } else {
        r = q;
      }
    }
    if(a < middle) {
      if(r == 0) { *a = ~*a; }
      ss_rotate(a, middle, last);
      last -= middle - a;
      middle = a;
      if(first == middle) { break; }
    }
    --last;
    if(x != 0) { while(*--last < 0) { } }
    if(middle == last) { break; }
  }
}

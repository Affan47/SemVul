_soxr_ordered_convolve_simd(int n, void * not_used, float * a, const float * b)
{
  int i;
  float ab0, ab1;
  v4sf       *  va = (v4sf       *)a;
  v4sf const *   RESTRICT   vb = (v4sf const *)b;
  assert(VALIGNED(a) && VALIGNED(b));
  ab0 = a[0] * b[0], ab1 = a[1] * b[1];
  for (i = 0; i < n / 4; i += 2) {
    v4sf a1r = va[i+0], a1i = va[i+1];
    v4sf b1r = vb[i+0], b1i = vb[i+1];
    UNINTERLEAVE2(a1r, a1i, a1r, a1i);
    UNINTERLEAVE2(b1r, b1i, b1r, b1i);
    VCPLXMUL(a1r, a1i, b1r, b1i);
    INTERLEAVE2(a1r, a1i, a1r, a1i);
    va[i+0] = a1r, va[i+1] = a1i;
  }
  a[0] = ab0, a[1] = ab1;
  (void)not_used;
}

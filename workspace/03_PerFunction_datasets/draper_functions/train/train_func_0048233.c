strscan_double(uint64_t x, TValue *o, int32_t ex2, int32_t neg)
{
  double n;


  if (LJ_UNLIKELY(ex2 <= -1075 && x != 0)) {

#if defined(__GNUC__) && LJ_64
    int32_t b = (int32_t)(__builtin_clzll(x)^63);
#else
    int32_t b = (x>>32) ? 32+(int32_t)lj_fls((uint32_t)(x>>32)) :
			  (int32_t)lj_fls((uint32_t)x);
#endif
    if ((int32_t)b + ex2 <= -1023 && (int32_t)b + ex2 >= -1075) {
      uint64_t rb = (uint64_t)1 << (-1075-ex2);
      if ((x & rb) && ((x & (rb+rb+rb-1)))) x += rb+rb;
      x = (x & ~(rb+rb-1));
    }
  }


  lua_assert((int64_t)x >= 0);
  n = (double)(int64_t)x;
  if (neg) n = -n;
  if (ex2) n = ldexp(n, ex2);
  o->n = n;
}

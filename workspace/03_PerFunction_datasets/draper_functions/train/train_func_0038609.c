caml_hash_mix_double(uint32 hash, double d)
{
  union {
    double d;
#if defined(ARCH_BIG_ENDIAN) || (defined(__arm__) && !defined(__ARM_EABI__))
    struct { uint32 h; uint32 l; } i;
#else
    struct { uint32 l; uint32 h; } i;
#endif
  } u;
  uint32 h, l;

  u.d = d;
  h = u.i.h; l = u.i.l;

  if ((h & 0x7FF00000) == 0x7FF00000 && (l | (h & 0xFFFFF)) != 0) {
    h = 0x7FF00000;
    l = 0x00000001;
  }

  else if (h == 0x80000000 && l == 0) {
    h = 0;
  }
  MIX(hash, l);
  MIX(hash, h);
  return hash;
}

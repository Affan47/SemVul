SuggestedDelayNS(int loop) {


#ifdef BASE_HAS_ATOMIC64
  static base::subtle::Atomic64 rand;
  uint64 r = base::subtle::NoBarrier_Load(&rand);
  r = 0x5deece66dLL * r + 0xb;
  base::subtle::NoBarrier_Store(&rand, r);

  r <<= 16;
  if (loop < 0 || loop > 32) {
    loop = 32;
  }


  return r >> (44 - (loop >> 3));
#else
  static Atomic32 rand;
  uint32 r = base::subtle::NoBarrier_Load(&rand);
  r = 0x343fd * r + 0x269ec3;
  base::subtle::NoBarrier_Store(&rand, r);

  r <<= 1;
  if (loop < 0 || loop > 32) {
    loop = 32;
  }


  return r >> (12 - (loop >> 3));
#endif
}

}

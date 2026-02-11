has_new_bits(u8* virgin_map) {

#ifdef __x86_64__

  u64* current = (u64*)trace_bits;
  u64* virgin  = (u64*)virgin_map;

  u32  i = (MAP_SIZE >> 3);

#else

  u32* current = (u32*)trace_bits;
  u32* virgin  = (u32*)virgin_map;

  u32  i = (MAP_SIZE >> 2);

#endif

  u8   ret = 0;

  while (i--) {

#ifdef __x86_64__

    u64 cur = *current;
    u64 vir = *virgin;

#else

    u32 cur = *current;
    u32 vir = *virgin;

#endif


    if (cur & vir) {

      if (ret < 2) {


#ifdef __x86_64__

        if (((cur & FFL(0)) && (vir & FFL(0)) == FFL(0)) ||
            ((cur & FFL(1)) && (vir & FFL(1)) == FFL(1)) ||
            ((cur & FFL(2)) && (vir & FFL(2)) == FFL(2)) ||
            ((cur & FFL(3)) && (vir & FFL(3)) == FFL(3)) ||
            ((cur & FFL(4)) && (vir & FFL(4)) == FFL(4)) ||
            ((cur & FFL(5)) && (vir & FFL(5)) == FFL(5)) ||
            ((cur & FFL(6)) && (vir & FFL(6)) == FFL(6)) ||
            ((cur & FFL(7)) && (vir & FFL(7)) == FFL(7))) ret = 2;
        else ret = 1;

#else

        if (((cur & FF(0)) && (vir & FF(0)) == FF(0)) ||
            ((cur & FF(1)) && (vir & FF(1)) == FF(1)) ||
            ((cur & FF(2)) && (vir & FF(2)) == FF(2)) ||
            ((cur & FF(3)) && (vir & FF(3)) == FF(3))) ret = 2;
        else ret = 1;

#endif

      }

      *virgin = vir & ~cur;

    }

    current++;
    virgin++;

  }

  if (ret && virgin_map == virgin_bits) bitmap_changed = 1;

  return ret;

}

caml_hash_mix_string(uint32 h, value s)
{
  mlsize_t len = caml_string_length(s);
  mlsize_t i;
  uint32 w;


  for (i = 0; i + 4 <= len; i += 4) {
#ifdef ARCH_BIG_ENDIAN
    w = Byte_u(s, i)
        | (Byte_u(s, i+1) << 8)
        | (Byte_u(s, i+2) << 16)
        | (Byte_u(s, i+3) << 24);
#else
    w = *((uint32 *) &Byte_u(s, i));
#endif
    MIX(h, w);
  }

  w = 0;
  switch (len & 3) {
  case 3: w  = Byte_u(s, i+2) << 16;
  case 2: w |= Byte_u(s, i+1) << 8;
  case 1: w |= Byte_u(s, i);
          MIX(h, w);
  default: ;
  }

  h ^= (uint32) len;
  return h;
}

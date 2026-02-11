sosemanuk_init_key(sosemanuk_master_state *state,
		   const uint8_t *key, size_t bitlength)
{
  uint32_t w[108];

  uint32_t i;
  int fullwords = bitlength / 32;
  for(i = 0; i < fullwords; ++i)
    w[i] = pack_littleendian(&key[i*4]);

  int partial = bitlength % 32;
  if(partial)
    {
      uint32_t tmp = 0;

      int j;
      int fullbytes = partial / 8;
      for(j = 0; j < fullbytes; ++j)
	tmp |= (uint32_t)key[i*4 + j] << (j*8);

      int bitpartial = partial % 8;
      if(bitpartial)
	{
	  uint8_t extra_bit = 1u << bitpartial;
	  tmp |= (uint32_t)((key[i*4 + j] & (extra_bit - 1)) | extra_bit)
	    << (j*8);
	}
      else
	{
	  tmp |= 1u << partial;
	}

      w[i++] = tmp;
    }
  else if(bitlength < 256)
    w[i++] = 1u;

  for(; i < 8; ++i)
    w[i] = 0;

  for(; i < 108; ++i)
    w[i] = rotl(w[i - 8] ^ w[i - 5] ^ w[i - 3] ^ w[i - 1] ^ 0x9e3779b9u ^ (i-8),
		11);


  for(i = 0; i < 8; ++i)
    {
      uint8_t sbox_idx = 7 - (i+4) % 8;
      int j;
      for(j = i; j < 25; j += 8)
	sbox_apply(sbox_idx, &w[8 + j*4], &state->k[j*4]);
    }
}

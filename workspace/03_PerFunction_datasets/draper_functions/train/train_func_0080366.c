dstar_dv_decode (const unsigned char * d, int data[3])
{
  int bits[3];
  int i;
  int errs;

  for (i=0; i < 3; i++)
  {
    bits[i] = 0;
  }

  for (i=0; i < 72; i++)
  {
    bits[ bit_pos1[i] ] |= (d[ i >> 3 ] & (0x80 >> (i & 0x07))) ? (1 << bit_pos2[i]) : 0;
  }

  errs = golay2412( bits[0], data );

  errs += golay2412( bits[1] ^ prng[ data[0] & 0x0fff ], data + 1 );

  data[2] = bits[2];

  return errs;
}

mpg123_getbits(int number_of_bits)
{
  unsigned long rval;

#ifdef DEBUG_GETBITS
  fprintf(stderr, "g%d", number_of_bits);
#endif

  if(!number_of_bits)
    return 0;

#if 0
  check_buffer_range(number_of_bits + bsi.bitindex);
#endif

  {
    rval = bsi.wordpointer[0];
    rval <<= 8;
    rval |= bsi.wordpointer[1];
    rval <<= 8;
    rval |= bsi.wordpointer[2];

    rval <<= bsi.bitindex;
    rval &= 0xffffff;

    bsi.bitindex += number_of_bits;

    rval >>= (24-number_of_bits);

    bsi.wordpointer += (bsi.bitindex >> 3);
    bsi.bitindex &= 7;
  }

#ifdef DEBUG_GETBITS
  fprintf(stderr,":%x ",rval);
#endif

  return rval;
}

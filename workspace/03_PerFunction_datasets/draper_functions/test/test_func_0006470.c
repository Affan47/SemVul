gt_determinebitspervalue(unsigned long maxvalue)
{
  unsigned int bits = 0;
  unsigned long value;

  for (value = maxvalue; value > 0; value >>= 1)
  {
    bits++;
  }
#define GT_MAXLOG2VALUE 63
  gt_assert(bits <= GT_MAXLOG2VALUE);
#ifdef USEbuiltin_clzl
  {
    unsigned int fastbits = (unsigned int) (sizeof(unsigned long) * CHAR_BIT) -
                            __builtin_clzl(maxvalue);
    if (bits != fastbits)
    {
      fprintf(stderr,"maxvalue=%lu: bits = %u != %d = clzl\n",
                        maxvalue,bits,fastbits);
      exit(EXIT_FAILURE);
    }
  }
#endif
  return bits;
}

disp_ufmt_binval(word32 *ap, word32 *bp, int32 blen)
{
 register int32 j;
 register word32 wrd;
 byte bval;
 int32 wi;

 for (wi = 0; wi < wlen_(blen); wi++)
  {
   wrd = ap[wi] & (bp[wi] ^ 0xffffffff);

#if defined(WORDS_BIGENDIAN)
   for (j = 24; j >= 0; j -= 8)
    {
     bval = (wrd >> j) & 0xff;
     addch_(bval);
    }
#else
   for (j = 0; j <= 24; j += 8)
    {
     bval = (wrd >> j) & 0xff;
     addch_(bval);
    }
#endif
  }
}

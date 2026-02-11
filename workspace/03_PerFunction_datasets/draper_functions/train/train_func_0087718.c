__ld_stval(register word32 *rgap, register word32 *rgbp,
 register byte *sbp, int32 blen)
{
 register int32 bi;
 int32 wlen;
 word32 tmpw;


 wlen = wlen_(blen);
 rgap[wlen - 1] = 0L;
 rgbp[wlen - 1] = 0L;
 for (bi = 0; bi < blen; bi++)
  {
   tmpw = (word32) sbp[bi];
   __lhsbsel(rgap, bi, tmpw & 1L);
   __lhsbsel(rgbp, bi, (tmpw >> 1) & 1L);
  }
}

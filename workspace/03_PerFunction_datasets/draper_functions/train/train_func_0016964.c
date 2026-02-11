init_utab(word32 *taddr, int32 blen)
{
 register int32 i;
 register word32 *wp;
 int32 wlen;

 wlen = wlen_(blen);


 for (wp = taddr, i = 0; i < wlen; i++) wp[i] = ALL1W;
 wp[wlen - 1] &= __masktab[ubits_(blen)];
}

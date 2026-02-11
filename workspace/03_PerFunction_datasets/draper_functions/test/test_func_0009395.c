rmd160_final( rmd160_context_t *hd )
{
  u32 t, msb, lsb;
  unsigned char *p;

  rmd160_write (hd, NULL, 0);

  t = hd->nblocks;

  lsb = t << 6;
  msb = t >> 26;

  t = lsb;
  if ((lsb += hd->count) < t)
    msb++;

  t = lsb;
  lsb <<= 3;
  msb <<= 3;
  msb |= t >> 29;

  if (hd->count < 56)
    {

      hd->buf[hd->count++] = 0x80;
      while (hd->count < 56)
        hd->buf[hd->count++] = 0;
    }
  else
    {

      hd->buf[hd->count++] = 0x80;
      while (hd->count < 64)
        hd->buf[hd->count++] = 0;
      rmd160_write (hd, NULL, 0);
      memset (hd->buf, 0, 56);
    }

  hd->buf[56] = lsb;
  hd->buf[57] = lsb >>  8;
  hd->buf[58] = lsb >> 16;
  hd->buf[59] = lsb >> 24;
  hd->buf[60] = msb;
  hd->buf[61] = msb >>  8;
  hd->buf[62] = msb >> 16;
  hd->buf[63] = msb >> 24;
  transform (hd, hd->buf);

  p = hd->buf;
#define X(a) do { *p++ = hd->h##a;       *p++ = hd->h##a >> 8;	\
                  *p++ = hd->h##a >> 16; *p++ = hd->h##a >> 24; } while(0)
  X(0);
  X(1);
  X(2);
  X(3);
  X(4);
#undef X
}

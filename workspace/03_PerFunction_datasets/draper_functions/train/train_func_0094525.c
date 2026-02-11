initSinTable (void)
{
  gint32 *tptr, *tsinptr;
  gint i;

  tsinptr = tptr = sintable;

  for (i = 0; i < 1024; i++)
    *tptr++ = (int) (sin (i * M_PI / 512) * 32767);

  for (i = 0; i < 256; i++)
    *tptr++ = *tsinptr++;
}

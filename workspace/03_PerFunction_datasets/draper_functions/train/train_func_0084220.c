putbox (int x, int y, int w, int h, void *b)
{
  uchar          *vp;
  uchar          *bp;
  int             i;
  ASSIGNVP8 (x, y, vp);
  bp = b;
  for (i = 0; i < h; i++)
    {
      __memcpy (vp, bp, w);

      vp += MAPWIDTH;
    }
}

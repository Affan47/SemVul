copy_screen_even (const a_pixel *s, a_pixel *d, unsigned width)
{
  int i;
  for (i = 200; i; --i, s += xbuf * 2, d += 2 * scr_pitch)
    fastmem4 (s, d, width / 4);
}

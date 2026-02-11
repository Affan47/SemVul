search_entry(int r, int g, int b)
{
  register RGBdb *db = rgbdb;
  int i, j, diffr, diffg, diffb;
  unsigned int diff, mindiff;

  mindiff = (unsigned int)~0;
  for (i = j = 0; db->r < 256; db++, i++)
  {
    diffr = r - db->r;
    diffg = g - db->g;
    diffb = b - db->b;

#ifdef FL_LINEAR
    diff = unsigned(3.0 * (FL_abs(r - db->r)) +
                    (5.9 * FL_abs(g - db->g)) +
                    (1.1 * (FL_abs(b - db->b))));
#else
    diff = unsigned(3.0 * (diffr *diffr) +
                    5.9 * (diffg *diffg) +
                    1.1 * (diffb *diffb));
#endif

    if (mindiff > diff)
    {
      mindiff = diff;
      j = i;
    }
  }

  return j;
}

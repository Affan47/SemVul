granulepos_to_key_granule_dirac (GstOggStream * pad, gint64 gp)
{
  gint64 pt;
  int dist_h;
  int dist_l;
  int dist;
  int delay;
  gint64 dt;

  if (gp == -1 || gp == 0)
    return gp;

  pt = ((gp >> 22) + (gp & OGG_DIRAC_GRANULE_LOW_MASK)) >> 9;
  dist_h = (gp >> 22) & 0xff;
  dist_l = gp & 0xff;
  dist = (dist_h << 8) | dist_l;
  delay = (gp >> 9) & 0x1fff;
  dt = pt - delay;

  return dt - 2 * dist + 4;
}

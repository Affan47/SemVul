height (FttCell * cell)
{
  if (!GFS_IS_MIXED (cell))
    return 1.;
  gdouble f = GFS_STATE (cell)->solid->s[FTT_FRONT];
  if (f == 0.)
    return 0.;
  guint level = ftt_cell_level (cell);
  g_assert (level <= MAXLEVEL);
  return GFS_STATE (cell)->solid->a/f*(1 << (MAXLEVEL - level));
}

cell_fraction (FttCell * cell)
{
  g_return_val_if_fail (cell != NULL, 0.);
  return GFS_IS_MIXED (cell) ? GFS_STATE (cell)->solid->a : 1.;
}

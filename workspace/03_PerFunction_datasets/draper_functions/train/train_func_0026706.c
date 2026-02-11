thin_cell_is_solid (FttCell * cell)
{
  gdouble sum = 0.;
  FttDirection d;

  for (d = 0; d < FTT_NEIGHBORS; d++)
    sum += GFS_STATE (cell)->solid->s[d];
  return (sum < FTT_NEIGHBORS/2);
}

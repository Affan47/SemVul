coarsen_cell (FttCell * cell, AdaptLocalParams * p)
{
  if (GFS_CELL_IS_BOUNDARY (cell))
    return COARSENABLE (cell, p);
  if (ftt_refine_corner (cell))
    return FALSE;
  return COARSENABLE (cell, p);
}

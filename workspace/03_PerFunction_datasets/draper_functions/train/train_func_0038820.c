deal_with_thin_cell (FttCell * cell, InitSolidParams * p)
{
  cell->flags |= GFS_FLAG_THIN;
  if (thin_cell_is_solid (cell))
    GFS_VALUE (cell, p->status) = GFS_STATUS_SOLID;
  else {
    GfsSolidVector * solid = GFS_STATE (cell)->solid;
    FttDirection d;
    for (d = 0; d < FTT_NEIGHBORS; d++)
      solid->s[d] = (solid->s[d] > 0.5);
    solid->a = 1.;
    ftt_cell_pos (cell, &solid->cm);
    solid->ca = solid->cm;
  }
}

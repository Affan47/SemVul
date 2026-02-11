interpolate_1D1_stencil (FttCell * cell,
				     FttDirection d,
				     guint v)
{
  FttCellFace f;

  GFS_VARIABLE (cell, v) = 1.;
  f = ftt_cell_face (cell, d);
  if (f.neighbor)
    average_neighbor_value_stencil (&f, v);
}

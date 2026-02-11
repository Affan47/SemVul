residual_set_dirichlet (FttCell * cell, RelaxParams * p)
{
  GfsGradient g;
  FttCellNeighbors neighbor;
  FttCellFace f;
  GfsGradient ng;

  g.a = GFS_VARIABLE (cell, p->dia);
  if (GFS_IS_MIXED (cell) && ((cell)->flags & GFS_FLAG_DIRICHLET) != 0)
    g.b = gfs_cell_dirichlet_gradient_flux (cell, p->u, p->maxlevel, GFS_STATE (cell)->solid->fv);
  else
    g.b = 0.;

  f.cell = cell;
  ftt_cell_neighbors (cell, &neighbor);
  for (f.d = 0; f.d < FTT_NEIGHBORS; f.d++) {
    f.neighbor = neighbor.c[f.d];
    gfs_face_cm_weighted_gradient (&f, &ng, p->u, p->maxlevel);
    g.a += ng.a;
    g.b += ng.b;
  }
  GFS_VARIABLE (cell, p->res) = GFS_VARIABLE (cell, p->rhs) -
    (g.b - GFS_VARIABLE (cell, p->u)*g.a);
}

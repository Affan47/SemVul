residual_set2D (FttCell * cell, RelaxParams * p)
{
  GfsGradient g;
  FttCellNeighbors neighbor;
  FttCellFace f;
  GfsGradient ng;

  g.a = GFS_VARIABLE (cell, p->dia);
  g.b = 0.;
  f.cell = cell;
  ftt_cell_neighbors (cell, &neighbor);
  for (f.d = 0; f.d < FTT_NEIGHBORS_2D; f.d++) {
    f.neighbor = neighbor.c[f.d];
    if (f.neighbor) {
      gfs_face_weighted_gradient_2D (&f, &ng, p->u, p->maxlevel);
      g.a += ng.a;
      g.b += ng.b;
    }
  }
  GFS_VARIABLE (cell, p->res) = GFS_VARIABLE (cell, p->rhs) -
    (g.b - GFS_VARIABLE (cell, p->u)*g.a);
}

get_from_above (FttCell * parent, GfsVariable * v)
{
  guint level = ftt_cell_level (parent);
  FttCellNeighbors n;
  FttCellChildren child;
  FttComponent c;
  FttVector h;
  guint i;

  ftt_cell_neighbors (parent, &n);
  for (c = 0; c < FTT_DIMENSION; c++) {
    FttCellFace f;
    GfsGradient g;
    gdouble g1, g2;

    f.cell = parent;
    f.d = 2*c;
    f.neighbor = n.c[f.d];
    gfs_face_gradient (&f, &g, v->i, level);
    g1 = g.b - g.a*GFS_VARIABLE (parent, v->i);
    f.d = 2*c + 1;
    f.neighbor = n.c[f.d];
    gfs_face_gradient (&f, &g, v->i, level);
    g2 = g.b - g.a*GFS_VARIABLE (parent, v->i);
    (&h.x)[c] = (g1 - g2)/2.;
  }

  ftt_cell_children (parent, &child);
  for (i = 0; i < FTT_CELLS; i++)
    if (child.c[i]) {
      FttVector p;

      GFS_VARIABLE (child.c[i], v->i) = GFS_VARIABLE (parent, v->i);
      ftt_cell_relative_pos (child.c[i], &p);
      for (c = 0; c < FTT_DIMENSION; c++)
	GFS_VARIABLE (child.c[i], v->i) += (&p.x)[c]*(&h.x)[c];
    }
}

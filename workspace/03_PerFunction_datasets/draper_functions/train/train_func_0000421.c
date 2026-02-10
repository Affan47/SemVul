moving_vof_cell_coarse_fine (FttCell * cell, GfsVariable * v)
{
  FttCell * parent = ftt_cell_parent (cell);
  GfsVariableTracerVOF * t = GFS_VARIABLE_TRACER_VOF (v);
  gdouble f = GFS_VALUE (parent, v);
  FttComponent c;
  guint i;

  if (GFS_IS_FULL (f)) {
    GFS_VALUE (cell, v) = f;
    for (c = 1; c < FTT_DIMENSION; c++)
	GFS_VALUE (cell, t->m[c]) = 0.;
      GFS_VALUE (cell, t->m[0]) = 1.;
      GFS_VALUE (cell, t->alpha) = f;
  }
  else {
    gdouble alpha = GFS_VALUE (parent, t->alpha);
    FttVector m;

    for (i = 0; i < FTT_DIMENSION; i++)
      (&m.x)[i] = GFS_VALUE (parent, t->m[i]);

    gdouble alpha1 = alpha;

    FttVector p;

    ftt_cell_relative_pos (cell, &p);
    for (c = 0; c < FTT_DIMENSION; c++) {
      alpha1 -= (&m.x)[c]*(0.25 + (&p.x)[c]);
      GFS_VALUE (cell, t->m[c]) = (&m.x)[c];
    }
    GFS_VALUE (cell, v) = gfs_plane_volume (&m, 2.*alpha1);
    GFS_VALUE (cell, t->alpha) = 2.*alpha1;
  }
}

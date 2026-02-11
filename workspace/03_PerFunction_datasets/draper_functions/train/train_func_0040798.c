add_vof_center (FttCell * cell, FttVector * p, guint level,
			    FttVector * origin,
			    GfsVariableTracerVOF * t,
			    ParabolaFit * fit, gdouble w)
{
  gdouble f = GFS_VALUE (cell, GFS_VARIABLE1 (t));
  if (!GFS_IS_FULL (f)) {
    FttVector m, c;
    gdouble alpha = gfs_vof_plane_interpolate (cell, p, level, t, &m);
    gdouble area = gfs_plane_area_center (&m, alpha, &c);
    gdouble h = ftt_level_size (level);
    FttComponent i;
    for (i = 0; i < FTT_DIMENSION; i++)
      (&c.x)[i] = ((&p->x)[i] - (&origin->x)[i])/h + (&c.x)[i] - 0.5;
    parabola_fit_add (fit, &c.x, w*area);
  }
}

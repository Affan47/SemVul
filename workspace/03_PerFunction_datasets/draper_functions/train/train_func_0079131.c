position (FttCell * cell, GfsVariable * v)
{
  FttVector p;

  if (gfs_vof_center (cell, GFS_VARIABLE_TRACER_VOF (GFS_VARIABLE_CURVATURE (v)->f), &p))
    GFS_VALUE (cell, v) = (&p.x)[GFS_VARIABLE_POSITION (v)->c] -
      GFS_VARIABLE_POSITION (v)->ref;
  else
    GFS_VALUE (cell, v) = GFS_NODATA;
}

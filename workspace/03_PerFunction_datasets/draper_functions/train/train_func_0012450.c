variable_distance_write (GtsObject * o, FILE * fp)
{
  (* GTS_OBJECT_CLASS (gfs_variable_distance_class ())->parent_class->write) (o, fp);

  fprintf (fp, " %s", GFS_VARIABLE_DISTANCE (o)->v->name);
  if (GFS_VARIABLE_DISTANCE (o)->stencil)
    fputs (" { stencil = 1 }", fp);
}

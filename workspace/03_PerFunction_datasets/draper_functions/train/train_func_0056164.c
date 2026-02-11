gfs_twisted_vertex_write (GtsObject * o, FILE * fp)
{
  if (GTS_OBJECT_CLASS (gfs_twisted_vertex_class ())->parent_class->write)
    (* GTS_OBJECT_CLASS (gfs_twisted_vertex_class ())->parent_class->write)
      (o, fp);
  fprintf (fp, " %g", GFS_TWISTED_VERTEX (o)->theta);
}

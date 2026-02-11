gfs_boundary_write (GtsObject * o, FILE * fp)
{
  GfsBoundary * b = GFS_BOUNDARY (o);
  gboolean any_extra = FALSE;

  if (GTS_OBJECT_CLASS (gfs_boundary_class ())->parent_class->write)
    (* GTS_OBJECT_CLASS (gfs_boundary_class ())->parent_class->write)
      (o, fp);

  g_hash_table_foreach (b->bc, (GHFunc) is_extra, &any_extra);
  if (any_extra) {
    fputs (" {\n", fp);
    g_hash_table_foreach (b->bc, (GHFunc) write_extra, fp);
    fputc ('}', fp);
  }
}

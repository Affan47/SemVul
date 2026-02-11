gfs_gedge_write (GtsObject * object, FILE * fp)
{
  fprintf (fp, " %s", ftt_direction_name [GFS_GEDGE (object)->d]);
  if (GFS_GEDGE (object)->rotate < FTT_NEIGHBORS)
    fprintf (fp, " %s", ftt_direction_name [GFS_GEDGE (object)->rotate]);
}

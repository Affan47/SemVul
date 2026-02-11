gfs_output_solid_force_write (GtsObject * o, FILE * fp)
{
  GfsOutputSolidForce * l = GFS_OUTPUT_SOLID_FORCE (o);
  (* GTS_OBJECT_CLASS (gfs_output_solid_force_class ())->parent_class->write) (o, fp);
  if (l->weight)
    gfs_function_write (l->weight, fp);
}

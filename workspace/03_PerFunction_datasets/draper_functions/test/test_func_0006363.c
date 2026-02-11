bc_subcritical_read (GtsObject ** o, GtsFile * fp)
{
  GfsBc * bc = GFS_BC (*o);

  if (GTS_OBJECT_CLASS (gfs_bc_subcritical_class ())->parent_class->read)
    (* GTS_OBJECT_CLASS (gfs_bc_subcritical_class ())->parent_class->read) (o, fp);
  if (fp->type == GTS_ERROR)
    return;

  if (!GFS_IS_RIVER (bc->v->domain)) {
    gts_file_error (fp, "GfsBcSubcritical only makes sense for GfsRiver simulations");
    return;
  }

  gfs_function_set_units (GFS_BC_VALUE (bc)->val, 1.);
}

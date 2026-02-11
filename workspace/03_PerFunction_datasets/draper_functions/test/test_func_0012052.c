gfs_adapt_gradient_read (GtsObject ** o, GtsFile * fp)
{
  (* GTS_OBJECT_CLASS (gfs_adapt_gradient_class ())->parent_class->read) (o, fp);
  if (fp->type == GTS_ERROR)
    return;

  GfsAdaptGradient * a = GFS_ADAPT_GRADIENT (*o);
  a->v = gfs_function_get_variable (GFS_ADAPT_FUNCTION (a)->f);
  if (a->v == NULL)
    a->v = gfs_temporary_variable (GFS_DOMAIN (gfs_object_simulation (a)));
  a->dimension = pow (gfs_object_simulation (a)->physical_params.L, a->v->units);
}

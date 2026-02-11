gfs_remove_droplets_read (GtsObject ** o, GtsFile * fp)
{
  if (GTS_OBJECT_CLASS (gfs_remove_droplets_class ())->parent_class->read)
    (* GTS_OBJECT_CLASS (gfs_remove_droplets_class ())->parent_class->read)
      (o, fp);
  if (fp->type == GTS_ERROR)
    return;

  if (fp->type != GTS_STRING) {
    gts_file_error (fp, "expecting a string (variable)");
    return;
  }
  GfsDomain * domain = GFS_DOMAIN (gfs_object_simulation (*o));
  GfsRemoveDroplets * r = GFS_REMOVE_DROPLETS (*o);
  if ((r->c = gfs_variable_from_name (domain->variables, fp->token->str)) == NULL) {
    gts_file_error (fp, "unknown variable `%s'", fp->token->str);
    return;
  }
  gts_file_next_token (fp);

  if (fp->type != GTS_INT) {
    gts_file_error (fp, "expecting an integer (min)");
    return;
  }
  GFS_REMOVE_DROPLETS (*o)->min = atoi (fp->token->str);
  gts_file_next_token (fp);

  if (fp->type != '\n') {
    r->fc = gfs_function_new (gfs_function_class (), 0.);
    gfs_function_read (r->fc, gfs_object_simulation (r), fp);
  }
}

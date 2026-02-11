variable_distance_read (GtsObject ** o, GtsFile * fp)
{
  GfsDomain * domain;

  (* GTS_OBJECT_CLASS (gfs_variable_distance_class ())->parent_class->read) (o, fp);
  if (fp->type == GTS_ERROR)
    return;

  if (fp->type != GTS_STRING) {
    gts_file_error (fp, "expecting a string (c)");
    return;
  }
  domain = GFS_DOMAIN (gfs_object_simulation (*o));
  if (!(GFS_VARIABLE_DISTANCE (*o)->v =
	gfs_variable_from_name (domain->variables, fp->token->str))) {
    gts_file_error (fp, "unknown variable `%s'", fp->token->str);
    return;
  }
  if (GFS_VARIABLE1 (*o)->description)
    g_free (GFS_VARIABLE1 (*o)->description);
  GFS_VARIABLE1 (*o)->description = g_strjoin (" ",
					       "Distance to the interface defined by tracer",
					       fp->token->str, NULL);
  gts_file_next_token (fp);

  if (fp->type == '{') {
    GtsFileVariable var[] = {
      {GTS_INT, "stencil", TRUE},
      {GTS_NONE}
    };
    var[0].data = &GFS_VARIABLE_DISTANCE (*o)->stencil;
    gts_file_assign_variables (fp, var);
  }
}

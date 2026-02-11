boundary_read_extra_bc (GfsBoundary * b, GtsFile * fp)
{
  gboolean ret = FALSE;

  if (fp->type != '{')
    return ret;

  fp->scope_max++;
  gts_file_next_token (fp);

  while (fp->type != GTS_ERROR && fp->type != '}') {
    if (fp->type == '\n') {
      gts_file_next_token (fp);
      continue;
    }
    if (fp->type != GTS_STRING) {
      gts_file_error (fp, "expecting a keyword");
      return ret;
    }
    else {
      GtsObjectClass * klass = gfs_object_class_from_name (fp->token->str);
      GtsObject * object;

      if (klass == NULL) {
	gts_file_error (fp, "unknown keyword `%s'", fp->token->str);
	return ret;
      }
      else if (!gts_object_class_is_from_class (klass, gfs_bc_class ())) {
	gts_file_error (fp, "`%s' is not a GfsBc", fp->token->str);
	return ret;
      }

      object = gts_object_new (klass);
      g_assert (klass->read);
      GFS_BC (object)->b = b;
      GFS_BC (object)->extra = TRUE;
      (* klass->read) (&object, fp);
      if (fp->type == GTS_ERROR) {
	gts_object_destroy (object);
	return ret;
      }

      gfs_boundary_add_bc (b, GFS_BC (object));
      ret = TRUE;
    }
  }
  if (fp->type != '}') {
    gts_file_error (fp, "expecting a closing brace");
    return ret;
  }
  fp->scope_max--;
  gts_file_next_token (fp);

  return ret;
}

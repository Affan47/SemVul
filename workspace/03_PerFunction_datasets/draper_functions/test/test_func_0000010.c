bc_flather_read (GtsObject ** o, GtsFile * fp)
{
  GfsBcFlather * bc = GFS_BC_FLATHER (*o);
  GfsDomain * domain = gfs_box_domain (GFS_BC (bc)->b->box);

  (* GTS_OBJECT_CLASS (gfs_bc_flather_class ())->parent_class->read) (o, fp);

  gfs_function_set_units (GFS_BC_VALUE (bc)->val, 1.);
  if (fp->type == GTS_ERROR)
    return;
  if (fp->type != GTS_STRING) {
    gts_file_error (fp, "expecting a string (h)");
    return;
  }
  bc->h = gfs_variable_from_name (domain->variables, fp->token->str);
  if (bc->h == NULL) {
    gts_file_error (fp, "unknown variable `%s'", fp->token->str);
    return;
  }
  gts_file_next_token (fp);
  if (fp->type != GTS_STRING) {
    gts_file_error (fp, "expecting a string (p)");
    return;
  }
  bc->p = gfs_variable_from_name (domain->variables, fp->token->str);
  if (bc->p == NULL) {
    gts_file_error (fp, "unknown variable `%s'", fp->token->str);
    return;
  }
  gts_file_next_token (fp);
  if (bc->val == NULL)
    bc->val = gfs_function_new (gfs_function_class (), 0.);
  gfs_function_read (bc->val, gfs_box_domain (GFS_BC (bc)->b->box), fp);
  gfs_function_set_units (bc->val, 1.);

  ftt_cell_traverse (GFS_BC (bc)->b->root, FTT_PRE_ORDER, FTT_TRAVERSE_ALL, -1,
		     (FttCellTraverseFunc) set_gradient_boundary, NULL);
}

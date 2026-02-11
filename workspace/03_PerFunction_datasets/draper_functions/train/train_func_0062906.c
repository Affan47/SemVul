gfs_source_tension_css_read (GtsObject ** o, GtsFile * fp)
{
  GfsSourceTensionCSS * s = GFS_SOURCE_TENSION_CSS (*o);
  GfsDomain * domain = GFS_DOMAIN (gfs_object_simulation (*o));
  FttComponent c;

  (* GTS_OBJECT_CLASS (gfs_source_tension_css_class ())->parent_class->read) (o, fp);
  if (fp->type == GTS_ERROR)
    return;

  for (c = 0; c < FTT_DIMENSION; c++) {
    static gchar * name[3] = {"_Tx", "_Ty", "_Tz"};
    if ((s->t[c] = gfs_variable_from_name (domain->variables, name[c])) == NULL)
      s->t[c] = gfs_domain_add_variable (domain, name[c], NULL);
  }
}

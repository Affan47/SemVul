gfs_domain_add_variable (GfsDomain * domain,
				       const gchar * name,
				       const gchar * description)
{
  GfsVariable * v;

  g_return_val_if_fail (domain != NULL, NULL);

  if ((v = gfs_variable_new (gfs_variable_class (), domain, name, description)) == NULL)
    return NULL;
  domain->variables = g_slist_append (domain->variables, v);
  return v;
}

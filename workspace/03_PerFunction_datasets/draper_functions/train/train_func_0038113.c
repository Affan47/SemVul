gfs_derived_variable_from_name (GSList * i, const gchar * name)
{
  g_return_val_if_fail (name != NULL, NULL);

  while (i) {
    GfsDerivedVariable * v = i->data;
    if (!strcmp (v->name, name))
      return v;
    i = i->next;
  }
  return NULL;
}

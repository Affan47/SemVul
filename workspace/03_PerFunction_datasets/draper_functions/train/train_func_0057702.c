all_entries (GConfSource *source,
             const char  *key,
             const char **locales,
             GError     **err)
{
  MarkupSource *ms = (MarkupSource*)source;
  MarkupDir *dir;
  GError* error;
  GSList *retval;
  GSList *tmp;

  retval = NULL;

  error = NULL;
  dir = markup_tree_lookup_dir (ms->tree, key, &error);
  if (error != NULL)
    {
      g_propagate_error (err, error);
      return NULL;
    }

  if (dir == NULL)
    return NULL;

  error = NULL;
  tmp = markup_dir_list_entries (dir, &error);
  if (error != NULL)
    {
      g_propagate_error (err, error);
      return NULL;
    }

  while (tmp != NULL)
    {
      retval = g_slist_prepend (retval,
                                gconf_entry_from_markup_entry (tmp->data,
                                                               locales));

      tmp = tmp->next;
    }

  return retval;
}

listify_foreach(const gchar* key, Entry* e, ListifyData* ld)
{
  GConfValue* val;
  GConfEntry* entry;
  GError* error = NULL;

  val = entry_get_value (e, ld->locales, &error);

  if (error != NULL)
    {
      g_assert (val == NULL);
      g_error_free (error);
      return;
    }

  entry = gconf_entry_new_nocopy (g_strdup(key),
                                  val ? gconf_value_copy(val) : NULL);

  if (entry_get_schema_name (e))
    {
      gconf_entry_set_schema_name (entry, entry_get_schema_name (e));
    }

  ld->list = g_slist_prepend(ld->list, entry);
}

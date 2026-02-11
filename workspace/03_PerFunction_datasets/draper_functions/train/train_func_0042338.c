query_metainfo (GConfSource *source,
                const char  *key,
                GError     **err)
{
  MarkupSource* ms = (MarkupSource*)source;
  GError* error = NULL;
  MarkupEntry *entry;

  error = NULL;
  entry = tree_lookup_entry (ms->tree, key, FALSE, &error);
  if (error != NULL)
    {
      g_propagate_error (err, error);
      return NULL;
    }

  if (entry != NULL)
    {
      GConfMetaInfo* gcmi;
      const char *schema_name;
      GTime mtime;
      const char *mod_user;

      gcmi = gconf_meta_info_new ();

      schema_name = markup_entry_get_schema_name (entry);
      mtime = markup_entry_get_mod_time (entry);
      mod_user = markup_entry_get_mod_user (entry);

      if (schema_name)
        gconf_meta_info_set_schema (gcmi, schema_name);

      gconf_meta_info_set_mod_time (gcmi, mtime);

      if (mod_user)
        gconf_meta_info_set_mod_user (gcmi, mod_user);

      return gcmi;
    }
  else
    {
      return NULL;
    }
}

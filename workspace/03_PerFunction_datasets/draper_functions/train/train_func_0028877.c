save_tree (MarkupDir  *dir,
	   gboolean    save_as_subtree,
	   guint       file_mode,
	   GError    **err)
{
  if (!save_as_subtree)
    {
      save_tree_with_locale (dir, FALSE, NULL, NULL, file_mode, err);
    }
  else
    {
      OtherLocalesForeachData other_locales_foreach_data;
      GHashTable *other_locales;


      other_locales = g_hash_table_new (g_str_hash, g_str_equal);

      save_tree_with_locale (dir,
                             TRUE,
                             NULL,
                             other_locales,
                             file_mode,
                             err);

      other_locales_foreach_data.dir         = dir;
      other_locales_foreach_data.file_mode   = file_mode;
      other_locales_foreach_data.first_error = NULL;

      g_hash_table_foreach (other_locales,
                            (GHFunc) other_locales_foreach,
                            &other_locales_foreach_data);

      if (other_locales_foreach_data.first_error != NULL)
        {
          if (err != NULL && *err == NULL)
            *err = other_locales_foreach_data.first_error;
          else
            g_error_free (other_locales_foreach_data.first_error);
        }

      g_hash_table_destroy (other_locales);
    }
}

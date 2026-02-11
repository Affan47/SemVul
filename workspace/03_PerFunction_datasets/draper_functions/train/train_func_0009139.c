dconf_gvdb_utils_read_file (const gchar  *filename,
                            gboolean     *file_missing,
                            GError      **error)
{
  DConfChangeset *database;
  GError *my_error = NULL;
  GvdbTable *table = NULL;
  gchar *contents;
  gsize size;

  if (g_file_get_contents (filename, &contents, &size, &my_error))
    {
      GBytes *bytes;

      bytes = g_bytes_new_take (contents, size);
      table = gvdb_table_new_from_bytes (bytes, FALSE, &my_error);
      g_bytes_unref (bytes);
    }


  if (g_error_matches (my_error, G_FILE_ERROR, G_FILE_ERROR_NOENT))
    g_clear_error (&my_error);


  if (my_error)
    {
      g_propagate_prefixed_error (error, my_error, "Cannot open dconf database: ");
      return NULL;
    }


  database = dconf_changeset_new_database (NULL);


  if (table != NULL)
    {
      gchar **names;
      gint n_names;
      gint i;

      names = gvdb_table_get_names (table, &n_names);
      for (i = 0; i < n_names; i++)
        {
          if (dconf_is_key (names[i], NULL))
            {
              GVariant *value;

              value = gvdb_table_get_value (table, names[i]);

              if (value != NULL)
                {
                  dconf_changeset_set (database, names[i], value);
                  g_variant_unref (value);
                }
            }

          g_free (names[i]);
        }

      gvdb_table_free (table);
      g_free (names);
    }

  if (file_missing)
    *file_missing = (table == NULL);

  return database;
}

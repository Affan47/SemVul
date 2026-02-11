dconf_changeset_seal (DConfChangeset *changeset)
{
  gsize prefix_length;
  gint n_items;

  if (changeset->is_sealed)
    return;

  changeset->is_sealed = TRUE;


  n_items = g_hash_table_size (changeset->table);


  if (n_items == 0)
    return;


  {
    GHashTableIter iter;
    const gchar *first;
    gboolean have_one;
    gpointer key;

    g_hash_table_iter_init (&iter, changeset->table);


    have_one = g_hash_table_iter_next (&iter, &key, NULL);
    g_assert (have_one);

    prefix_length = strlen (key);
    first = key;


    while (g_hash_table_iter_next (&iter, &key, NULL))
      {
        const gchar *this = key;
        gint i;

        for (i = 0; i < prefix_length; i++)
          if (first[i] != this[i])
            {
              prefix_length = i;
              break;
            }
      }


    g_assert (prefix_length > 0);
    g_assert (first[0] == '/');


    if (n_items > 1)
      {
        while (first[prefix_length - 1] != '/')
          prefix_length--;
      }

    changeset->prefix = g_strndup (first, prefix_length);
  }


  {
    GHashTableIter iter;
    gpointer key;
    gint i = 0;

    changeset->paths = g_new (const gchar *, n_items + 1);

    g_hash_table_iter_init (&iter, changeset->table);
    while (g_hash_table_iter_next (&iter, &key, NULL))
      {
        const gchar *path = key;

        changeset->paths[i++] = path + prefix_length;
      }
    changeset->paths[i] = NULL;
    g_assert (i == n_items);


    qsort (changeset->paths, n_items, sizeof (const gchar *), dconf_changeset_string_ptr_compare);
  }


  {
    gint i;

    changeset->values = g_new (GVariant *, n_items);

    for (i = 0; i < n_items; i++)


      changeset->values[i] = g_hash_table_lookup (changeset->table, changeset->paths[i] - prefix_length);
  }
}

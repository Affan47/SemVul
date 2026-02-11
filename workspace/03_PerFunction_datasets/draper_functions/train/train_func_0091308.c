gconf_client_add_dir     (GConfClient* client,
                          const gchar* dirname,
                          GConfClientPreloadType preload,
                          GError** err)
{
  Dir* d;
  guint notify_id = 0;
  GError* error = NULL;

  g_return_if_fail (gconf_valid_key (dirname, NULL));

  trace ("Adding directory '%s'", dirname);

  d = g_hash_table_lookup (client->dir_hash, dirname);

  if (d == NULL)
    {
      Dir *overlap_dir;

      overlap_dir = setup_overlaps (client, dirname);


      if (overlap_dir == NULL)
        {
          trace ("REMOTE: Adding notify to engine at '%s'",
                 dirname);
          PUSH_USE_ENGINE (client);
          notify_id = gconf_engine_notify_add (client->engine,
                                               dirname,
                                               notify_from_server_callback,
                                               client,
                                               &error);
          POP_USE_ENGINE (client);


          g_return_if_fail ( (notify_id != 0 && error == NULL) ||
                             (notify_id == 0 && error != NULL) );


          if (handle_error (client, error, err))
            return;

          g_assert (error == NULL);
        }
      else
        {
          notify_id = 0;
        }

      d = dir_new (dirname, notify_id);

      g_hash_table_insert (client->dir_hash, d->name, d);

      gconf_client_preload (client, dirname, preload, &error);

      handle_error (client, error, err);
    }

  g_assert (d != NULL);

  d->add_count += 1;
}

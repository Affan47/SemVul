book_manager_monitor_path (DhBookManager *book_manager,
                           const gchar   *path)
{
        GFileMonitor      *file_monitor;
        GFile             *file;
        DhBookManagerPriv *priv;

        priv = GET_PRIVATE (book_manager);

        file = g_file_new_for_path (path);


        if (priv->monitors &&
            g_hash_table_lookup (priv->monitors, file)) {
                return;
        }


        file_monitor = g_file_monitor_directory (file,
                                                 G_FILE_MONITOR_NONE,
                                                 NULL,
                                                 NULL);
        if (file_monitor) {

                g_signal_connect (file_monitor, "changed",
                                  G_CALLBACK (book_manager_booklist_monitor_event_cb),
                                  book_manager);


                if (G_UNLIKELY (!priv->monitors)) {
                        priv->monitors = g_hash_table_new_full (g_file_hash,
                                                                (GEqualFunc) g_file_equal,
                                                                (GDestroyNotify) g_object_unref,
                                                                (GDestroyNotify) g_object_unref);
                }


                g_hash_table_insert (priv->monitors,
                                     g_object_ref (file),
                                     file_monitor);
        } else {
                g_warning ("Couldn't setup to monitor changes on directory '%s'",
                           path);
        }

        g_object_unref (file);
}

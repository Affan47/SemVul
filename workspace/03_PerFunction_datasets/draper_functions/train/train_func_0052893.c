next_user_dirs_cb (GObject *object, GAsyncResult *res, gpointer user_data)
{
    GFileEnumerator *enumerator = G_FILE_ENUMERATOR (object);
    SharedDataManager *manager = SHARED_DATA_MANAGER (user_data);
    GList *link;
    GError *error = NULL;

    GList *files = g_file_enumerator_next_files_finish (enumerator, res, &error);
    if (error)
    {
        g_warning ("Could not enumerate user data directory %s: %s", USERS_DIR, error->message);
        g_clear_error (&error);
        g_object_unref (manager);
        return;
    }

    for (link = files; link; link = link->next)
    {
        GFileInfo *info = link->data;
        g_hash_table_insert (manager->priv->starting_dirs, g_strdup (g_file_info_get_name (info)), NULL);
    }

    if (files != NULL)
    {
        g_list_free_full (files, g_object_unref);
        g_file_enumerator_next_files_async (enumerator, NUM_ENUMERATION_FILES, G_PRIORITY_DEFAULT, NULL, next_user_dirs_cb, manager);
    }
    else
    {


        GList *users = common_user_list_get_users (common_user_list_get_instance ());
        for (link = users; link; link = link->next)
        {
            CommonUser *user = link->data;
            g_hash_table_remove (manager->priv->starting_dirs, common_user_get_name (user));
        }
        g_hash_table_foreach (manager->priv->starting_dirs, delete_unused_user, manager);
        g_hash_table_destroy (manager->priv->starting_dirs);
        manager->priv->starting_dirs = NULL;

        g_object_unref (manager);
    }
}

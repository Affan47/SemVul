gnc_tree_view_account_restore(GncTreeViewAccount *view,
                              AccountFilterDialog *fd,
                              GKeyFile *key_file, const gchar *group_name)
{
    GError *error = NULL;
    gchar *key, *value;
    gint i, count;
    gboolean show;


    show = g_key_file_get_boolean(key_file, group_name, SHOW_HIDDEN, &error);
    if (error)
    {
        g_warning("error reading group %s key %s: %s",
                  group_name, SHOW_HIDDEN, error->message);
        g_error_free(error);
        error = NULL;
        show = TRUE;
    }
    fd->show_hidden = show;

    show = g_key_file_get_boolean(key_file, group_name, SHOW_ZERO, &error);
    if (error)
    {
        g_warning("error reading group %s key %s: %s",
                  group_name, SHOW_ZERO, error->message);
        g_error_free(error);
        error = NULL;
        show = TRUE;
    }
    fd->show_zero_total = show;

    i = g_key_file_get_integer(key_file, group_name, ACCT_TYPES, &error);
    if (error)
    {
        g_warning("error reading group %s key %s: %s",
                  group_name, ACCT_TYPES, error->message);
        g_error_free(error);
        error = NULL;
        i = -1;
    }
    fd->visible_types = i;


    count = g_key_file_get_integer(key_file, group_name, ACCT_COUNT, &error);
    if (error == NULL)
    {
        for (i = 1; i <= count; i++)
        {
            key = g_strdup_printf(ACCT_OPEN, i);
            value = g_key_file_get_string(key_file, group_name, key, &error);
            if (error)
            {
                g_warning("error reading group %s key %s: %s",
                          group_name, key, error->message);
                g_error_free(error);
                error = NULL;
            }
            else
            {
                tree_restore_expanded_row(view, value);
                g_free(value);
            }
            g_free(key);
        }
    }
    else
    {
        g_warning("error reading group %s key %s: %s",
                  group_name, ACCT_COUNT, error->message);
        g_error_free(error);
    }


    value = g_key_file_get_string(key_file, group_name, ACCT_SELECTED, NULL);
    if (value)
    {
        tree_restore_selected_row(view, value);
        g_free(value);
    }


    gnc_tree_view_account_refilter(view);
}

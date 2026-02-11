db_get_build_cb (gpointer user_data,
                 gint n_columns,
                 gchar **column_values,
                 gchar **column_names)
{
        gchar **build = user_data;

        if (*build == NULL)
        {
                g_assert (n_columns > 0);
                *build = g_strdup (column_values[0]);
        }

        return 0;
}

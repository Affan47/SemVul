properties_update_clones (GtkTreeModel *model,
                          GtkTreeIter *iter)
{
        GtkBox *box;
        GList *children;
        gchar **result = NULL;
        gchar *game;
        gint rows, columns, ii;
        GError *error = NULL;

        box = GTK_BOX (GVA_WIDGET_PROPERTIES_ORIGINAL_LINKS);
        children = gtk_container_get_children (GTK_CONTAINER (box));
        g_list_foreach (children, (GFunc) gtk_widget_destroy, NULL);
        g_list_free (children);

        gtk_tree_model_get (
                model, iter, GVA_GAME_STORE_COLUMN_CLONEOF, &game, -1);

        if (game != NULL)
        {
                gchar *sql;

                sql = g_strdup_printf (SQL_SELECT_PARENT, game);
                if (!gva_db_get_table (sql, &result, &rows, &columns, &error))
                {
                        gva_error_handle (&error);
                        rows = columns = 0;
                }
                g_free (sql);
                g_free (game);
        }
        else
                rows = columns = 0;

        if (rows > 0)
                gtk_widget_show (GVA_WIDGET_PROPERTIES_ORIGINAL_VBOX);
        else
                gtk_widget_hide (GVA_WIDGET_PROPERTIES_ORIGINAL_VBOX);

        for (ii = 0; ii < rows; ii++)
        {
                const gchar *parent_name;
                const gchar *description;
                gboolean available;
                gchar **values;

                values = result + ((ii + 1) * columns);

                parent_name = values[0];
                description = values[1];
                available = (*values[2] == '1');

                properties_add_game_label (
                        box, parent_name, description, available);
        }

        g_strfreev (result);
        result = NULL;

        box = GTK_BOX (GVA_WIDGET_PROPERTIES_ALTERNATE_LINKS);
        children = gtk_container_get_children (GTK_CONTAINER (box));
        g_list_foreach (children, (GFunc) gtk_widget_destroy, NULL);
        g_list_free (children);

        gtk_tree_model_get (
                model, iter, GVA_GAME_STORE_COLUMN_NAME, &game, -1);

        if (game != NULL)
        {
                gchar *sql;

                sql = g_strdup_printf (SQL_SELECT_CLONES, game);
                if (!gva_db_get_table (sql, &result, &rows, &columns, &error))
                {
                        gva_error_handle (&error);
                        rows = columns = 0;
                }
                g_free (sql);
                g_free (game);
        }
        else
                rows = columns = 0;

        if (rows > 0)
                gtk_widget_show (GVA_WIDGET_PROPERTIES_ALTERNATE_VBOX);
        else
                gtk_widget_hide (GVA_WIDGET_PROPERTIES_ALTERNATE_VBOX);

        for (ii = 0; ii < rows; ii++)
        {
                const gchar *clone_name;
                const gchar *description;
                gboolean available;
                gchar **values;

                values = result + ((ii + 1) * columns);

                clone_name = values[0];
                description = values[1];
                available = (*values[2] == '1');

                properties_add_game_label (
                        box, clone_name, description, available);
        }

        g_strfreev (result);
}

gva_columns_get_names (GtkTreeView *view,
                       gboolean visible_only)
{
        GList *list;
        GSList *names = NULL;

        g_return_val_if_fail (GTK_IS_TREE_VIEW (view), NULL);

        list = g_list_reverse (gtk_tree_view_get_columns (view));

        while (list != NULL)
        {
                GtkTreeViewColumn *column = list->data;
                gboolean visible;

                visible = gtk_tree_view_column_get_visible (column);

                if (visible || !visible_only)
                        names = g_slist_prepend (
                                names, g_object_get_data (
                                G_OBJECT (column), "name"));

                list = g_list_delete_link (list, list);
        }

        return names;
}

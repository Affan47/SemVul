on_exclusions_clicked(GtkButton *sender, gpointer e) {
    GtkWidget *dlg = GTK_WIDGET(gtk_builder_get_object (builder, "prefs_exclusions_dialog"));
    GtkWidget *tree = GTK_WIDGET(gtk_builder_get_object (builder, "exclusion_list"));
    GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
    GtkTreeViewColumn *column = gtk_tree_view_column_new();
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gchar *temp = prefs_get_string("exclude_file_mask");

    gtk_window_set_transient_for(GTK_WINDOW (dlg), notebook_get_parent_window());

    if (temp) {
        gint i;
        gchar **masks = g_strsplit(temp, ";", 0);
        GtkTreeIter iter;

        g_free(temp);

        for (i = 0; masks[i]; i++) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, masks[i], -1);
        }

        g_strfreev(masks);
    }

    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_set_attributes(column, renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (tree), column);
    gtk_tree_view_set_model(GTK_TREE_VIEW (tree), GTK_TREE_MODEL (store));
    g_object_unref(store);

    gtk_builder_connect_signals(builder, NULL);
    gtk_dialog_run(GTK_DIALOG (dlg));
    gtk_widget_hide(dlg);
}

update_settings_cb (GtkTreeSelection *selection, gpointer user_data)
{
        GtkBuilder *builder = GTK_BUILDER (user_data);
        GtkTreeModel *model;
        GtkTreeIter iter;
        gchar *active_id;
        GtkWidget *treeview;
        GSettings *locale_settings;

        if (!gtk_tree_selection_get_selected (selection, &model, &iter)) {
                return;
        }
        gtk_tree_model_get (model, &iter, 0, &active_id, -1);

        treeview = GTK_WIDGET (gtk_builder_get_object (builder, "region_selector"));

        locale_settings = g_object_get_data (G_OBJECT (treeview), "settings");

        set_formats_locale (active_id);
        locale_settings_changed (locale_settings, NULL, builder);

        g_free (active_id);
}

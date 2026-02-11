plugin_stats_destroy(GtkWidget * container)
{
    if (plugin_stat_xml)
    {
        GtkWidget *vbox = (GtkWidget *) gtk_builder_get_object(plugin_stat_xml, "plugin_stats_vbox");
        GtkTreeModel *model =
            gtk_tree_view_get_model(GTK_TREE_VIEW(gtk_builder_get_object(plugin_stat_xml, "plugin_stats_tree")));
        gtk_container_remove(GTK_CONTAINER(container), vbox);
        if (model)
            g_object_unref(model);
        g_object_unref(plugin_stat_xml);
        plugin_stat_xml = NULL;
    }
}

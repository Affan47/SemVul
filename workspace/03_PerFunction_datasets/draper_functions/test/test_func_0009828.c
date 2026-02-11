forget_network_connection_delete_cb (NMRemoteConnection *connection,
                                     GError *error,
                                     gpointer user_data)
{
        gboolean ret;
        GtkTreeIter iter;
        GtkTreeModel *model;
        GtkTreeView *treeview;

        NetDeviceWifi *device_wifi = NET_DEVICE_WIFI (user_data);

        if (error != NULL) {
                g_warning ("failed to delete connection %s: %s",
                           nm_object_get_path (NM_OBJECT (connection)),
                           error->message);
                return;
        }


        treeview = GTK_TREE_VIEW (gtk_builder_get_object (device_wifi->priv->builder,
                                                         "treeview_list"));
        model = gtk_tree_view_get_model (treeview);
        ret = find_connection_id_in_store (model, &iter,
                                           device_wifi->priv->selected_connection_id);
        if (ret)
                gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
        show_wifi_list (device_wifi);
}

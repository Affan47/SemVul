show_wifi_details (NetDeviceWifi *device_wifi,
                   GtkTreeView *tv,
                   GtkTreePath *path)
{
        GtkWidget *widget;
        gboolean ret;
        gboolean in_range;
        GtkTreeModel *model;
        GtkTreeIter iter;
        gchar *path_str;

        model = gtk_tree_view_get_model (tv);
        path_str = gtk_tree_path_to_string (path);
        ret = gtk_tree_model_get_iter_from_string (model, &iter, path_str);
        if (!ret)
                goto out;


        g_free (device_wifi->priv->selected_connection_id);
        g_free (device_wifi->priv->selected_ssid_title);
        gtk_tree_model_get (model, &iter,
                            COLUMN_ACCESS_POINT_ID, &device_wifi->priv->selected_ap_id,
                            COLUMN_CONNECTION_ID, &device_wifi->priv->selected_connection_id,
                            COLUMN_TITLE, &device_wifi->priv->selected_ssid_title,
                            COLUMN_AP_IN_RANGE, &in_range,
                            -1);
        g_debug ("ssid = %s, in-range = %i",
                 device_wifi->priv->selected_ssid_title, in_range);

        widget = GTK_WIDGET (gtk_builder_get_object (device_wifi->priv->builder, "notebook_view"));

        nm_device_wifi_refresh_ui (device_wifi);
        gtk_notebook_set_current_page (GTK_NOTEBOOK (widget), 1);

out:
        g_free (path_str);
}

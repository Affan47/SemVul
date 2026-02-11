remove_media_server (GUPnPDeviceProxy *proxy)
{
        GUPnPDeviceInfo *info;
        GtkTreeModel    *model;
        GtkTreeIter      iter;
        const char      *udn;

        info = GUPNP_DEVICE_INFO (proxy);

        model = gtk_tree_view_get_model (GTK_TREE_VIEW (treeview));
        g_assert (model != NULL);

        udn = gupnp_device_info_get_udn (info);

        if (find_row (model,
                      NULL,
                      &iter,
                      compare_media_server,
                      (gpointer) udn,
                      FALSE)) {
                unschedule_icon_update (info);
                gtk_tree_store_remove (GTK_TREE_STORE (model), &iter);
        }
}

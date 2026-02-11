ario_connection_widget_autohosts_changed_cb (ArioAvahi *avahi,
                                             ArioConnectionWidget *connection_widget)
{
        ARIO_LOG_FUNCTION_START;
        GtkTreeIter iter;
        GSList *hosts;
        char tmp[INTLEN];


        gtk_list_store_clear (connection_widget->priv->autodetect_model);


        for (hosts = ario_avahi_get_hosts (avahi); hosts; hosts = g_slist_next (hosts)) {
                ArioHost *host = hosts->data;
                gtk_list_store_append (connection_widget->priv->autodetect_model, &iter);
                g_snprintf (tmp, INTLEN, "%d", host->port);
                gtk_list_store_set (connection_widget->priv->autodetect_model, &iter,
                                    NAME_COLUMN, host->name,
                                    HOST_COLUMN, host->host,
                                    PORT_COLUMN, tmp,
                                    -1);
        }


        if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (connection_widget->priv->autodetect_model), &iter))
                gtk_tree_selection_select_iter (connection_widget->priv->autodetect_selection, &iter);
}

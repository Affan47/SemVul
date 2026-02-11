mud_connection_view_cancel_dl_cb(GtkWidget *widget, MudConnectionView *view)
{
    MudMSPDownloadItem *item;

    gtk_widget_hide(view->priv->progressbar);
    gtk_widget_hide(view->priv->dl_label);
    gtk_widget_hide(view->priv->dl_button);

    if(view->priv->dl_conn)
    {
        gnet_conn_http_delete(view->priv->dl_conn);
        view->priv->dl_conn = NULL;
    }

    item = g_queue_pop_head(view->priv->download_queue);
    mud_telnet_msp_download_item_free(item);

    view->priv->downloading = FALSE;

    if(!g_queue_is_empty(view->priv->download_queue))
        mud_connection_view_start_download(view);
}

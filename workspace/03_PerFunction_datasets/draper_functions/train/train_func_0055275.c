response_callback(GtkDialog *dialog, gint response, gpointer user_data) {
    AuiServiceDialog *d = AUI_SERVICE_DIALOG(user_data);

    if ((response == GTK_RESPONSE_ACCEPT ||
        response == GTK_RESPONSE_OK ||
        response == GTK_RESPONSE_YES ||
        response == GTK_RESPONSE_APPLY) &&
        ((d->priv->resolve_service && !d->priv->resolve_service_done) ||
         (d->priv->resolve_host_name && !d->priv->resolve_host_name_done))) {

        GtkTreeIter iter;
        gint interface, protocol;
        gchar *name, *type;
        GdkCursor *cursor;

        g_signal_stop_emission(dialog, g_signal_lookup("response", gtk_dialog_get_type()), 0);
        d->priv->forward_response_id = response;

        if (d->priv->resolver)
            return;

        g_return_if_fail(gtk_tree_selection_get_selected(gtk_tree_view_get_selection(GTK_TREE_VIEW(d->priv->service_tree_view)), NULL, &iter));

        gtk_tree_model_get(GTK_TREE_MODEL(d->priv->service_list_store), &iter,
                           SERVICE_COLUMN_IFACE, &interface,
                           SERVICE_COLUMN_PROTO, &protocol,
                           SERVICE_COLUMN_NAME, &name,
                           SERVICE_COLUMN_TYPE, &type, -1);

        g_return_if_fail(d->priv->client);

        gtk_widget_set_sensitive(GTK_WIDGET(dialog), FALSE);
        cursor = gdk_cursor_new(GDK_WATCH);
        gdk_window_set_cursor(gtk_widget_get_window(GTK_WIDGET(dialog)), cursor);
        g_object_unref(G_OBJECT(cursor));

        if (!(d->priv->resolver = avahi_service_resolver_new(
                      d->priv->client, interface, protocol, name, type, d->priv->domain,
                      d->priv->address_family, !d->priv->resolve_host_name ? AVAHI_LOOKUP_NO_ADDRESS : 0, resolve_callback, d))) {

            GtkWidget *m = gtk_message_dialog_new(GTK_WINDOW(d),
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_CLOSE,
                                                  _("Failed to create resolver for %s of type %s in domain %s: %s"),
                                                  name, type, d->priv->domain,
                                                  avahi_strerror(avahi_client_errno(d->priv->client)));
            gtk_dialog_run(GTK_DIALOG(m));
            gtk_widget_destroy(m);

            gtk_dialog_response(GTK_DIALOG(d), GTK_RESPONSE_CANCEL);
            return;
        }
    }
}

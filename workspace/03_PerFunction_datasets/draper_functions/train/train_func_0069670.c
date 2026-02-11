resolve_callback(
        AvahiServiceResolver *r G_GNUC_UNUSED,
        AvahiIfIndex interface G_GNUC_UNUSED,
        AvahiProtocol protocol G_GNUC_UNUSED,
        AvahiResolverEvent event,
        const char *name,
        const char *type,
        const char *domain,
        const char *host_name,
        const AvahiAddress *a,
        uint16_t port,
        AvahiStringList *txt,
        AvahiLookupResultFlags flags G_GNUC_UNUSED,
        void *userdata) {

    AuiServiceDialog *d = AUI_SERVICE_DIALOG(userdata);

    switch (event) {
        case AVAHI_RESOLVER_FOUND:

            d->priv->resolve_service_done = 1;

            g_free(d->priv->service_name);
            d->priv->service_name = g_strdup(name);

            g_free(d->priv->service_type);
            d->priv->service_type = g_strdup(type);

            g_free(d->priv->domain);
            d->priv->domain = g_strdup(domain);

            g_free(d->priv->host_name);
            d->priv->host_name = g_strdup(host_name);

            d->priv->port = port;

            avahi_string_list_free(d->priv->txt_data);
            d->priv->txt_data = avahi_string_list_copy(txt);

            if (a) {
                d->priv->resolve_host_name_done = 1;
                d->priv->address = *a;
            }

            gtk_dialog_response(GTK_DIALOG(d), d->priv->forward_response_id);

            break;

        case AVAHI_RESOLVER_FAILURE: {
            GtkWidget *m = gtk_message_dialog_new(GTK_WINDOW(d),
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_CLOSE,
                                                  _("Avahi resolver failure: %s"),
                                                  avahi_strerror(avahi_client_errno(d->priv->client)));
            gtk_dialog_run(GTK_DIALOG(m));
            gtk_widget_destroy(m);

            gtk_dialog_response(GTK_DIALOG(d), GTK_RESPONSE_CANCEL);
            break;
        }
    }
}

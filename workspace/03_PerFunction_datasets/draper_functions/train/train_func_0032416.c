_avahi_service_browser_cb(AvahiServiceBrowser * b, AvahiIfIndex interface,
                          AvahiProtocol protocol, AvahiBrowserEvent event,
                          const char *name, const char *type,
                          const char *domain, AvahiLookupResultFlags flags,
                          void *userdata) {
    GaServiceBrowser *self = GA_SERVICE_BROWSER(userdata);
    GaServiceBrowserPrivate *priv = GA_SERVICE_BROWSER_GET_PRIVATE(self);
    if (priv->browser == NULL) {
        priv->browser = b;
    }
    g_assert(priv->browser == b);

    switch (event) {
        case AVAHI_BROWSER_NEW:
        case AVAHI_BROWSER_REMOVE:{
                guint signalid;
                signalid = (event == AVAHI_BROWSER_NEW ? NEW : REMOVED);
                g_signal_emit(self, signals[signalid], 0,
                              interface, protocol, name, type, domain, flags);
                break;
            }
        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            g_signal_emit(self, signals[CACHE_EXHAUSTED], 0);
            break;
        case AVAHI_BROWSER_ALL_FOR_NOW:
            g_signal_emit(self, signals[ALL_FOR_NOW], 0);
            break;
        case AVAHI_BROWSER_FAILURE:{
                GError *error;
                int aerrno = avahi_client_errno(priv->client->avahi_client);
                error = g_error_new(GA_ERROR, aerrno,
                                    "Browsing failed: %s",
                                    avahi_strerror(aerrno));
                g_signal_emit(self, signals[FAILURE], 0, error);
                g_error_free(error);
                break;
            }
    }
}

service_proxy_available_cb (G_GNUC_UNUSED GUPnPControlPoint *cp,
                            GUPnPServiceProxy               *proxy)
{
        GUPnPServiceInfo *info;
        GUPnPServiceIntrospection *introspection;
        GError *error = NULL;

        info = GUPNP_SERVICE_INFO (proxy);

        if (async) {
                gupnp_service_info_get_introspection_async_full (info,
                                                                 got_introspection,
                                                                 cancellable,
                                                                 NULL);
        } else {
                introspection =
                        gupnp_service_info_get_introspection (info, &error);
                got_introspection (info, introspection, error, NULL);

                if (error)
                        g_error_free (error);
        }
}

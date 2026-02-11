start_transfer (const char        *file_path,
                const char        *dest_uri,
                GUPnPServiceProxy *cds_proxy,
                GUPnPContext      *context)
{
        char *source_uri;
        char *file_name;

        if (!g_path_is_absolute (file_path)) {
                g_critical ("Given file path '%s' is not absolute.", file_path);

                transfer_completed ();

                return;
        }


        gupnp_context_host_path (context, file_path, file_path);

        source_uri = g_strdup_printf ("http://%s:%u%s",
                                      gupnp_context_get_host_ip (context),
                                      gupnp_context_get_port (context),
                                      file_path);

        file_name = g_path_get_basename (file_path);
        gupnp_service_proxy_begin_action (cds_proxy,
                                          "ImportResource",
                                          import_resource_cb,
                                          file_name,
                                          "SourceURI",
                                                G_TYPE_STRING,
                                                source_uri,
                                          "DestinationURI",
                                                G_TYPE_STRING,
                                                dest_uri,
                                          NULL);

        g_free (source_uri);
}

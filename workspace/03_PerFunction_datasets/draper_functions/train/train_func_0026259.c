main(int argc, char **argv)
{
    DMAPMdnsBrowser *browser;
    GError *error = NULL;

    if (argc == 2)
        conn_type = atoi (argv[1]);

    loop = g_main_loop_new (NULL, FALSE);

    if (conn_type == DAAP)
        browser = dmap_mdns_browser_new (DMAP_MDNS_BROWSER_SERVICE_TYPE_DAAP);
    else
        browser = dmap_mdns_browser_new (DMAP_MDNS_BROWSER_SERVICE_TYPE_DPAP);
    g_signal_connect (G_OBJECT (browser),
                      "service-added",
                      G_CALLBACK (service_added_cb),
                      NULL);
    g_debug ("starting mdns browser");
    dmap_mdns_browser_start (browser, &error);
    if (error) {
        g_warning ("error starting browser. code: %d message: %s",
                error->code,
                error->message);
        return 1;
    }

    g_main_loop_run (loop);

    return 0;
}

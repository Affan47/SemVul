display_dispose_check (GdmXdmcpDisplayFactory *factory,
                       const char             *hostname,
                       int                     display_num)
{
        RemoveHostData  *data;
        GdmDisplayStore *store;

        if (hostname == NULL) {
                return;
        }

        store = gdm_display_factory_get_display_store (GDM_DISPLAY_FACTORY (factory));

        g_debug ("GdmXdmcpDisplayFactory: display_dispose_check (%s:%d)",
                hostname ? hostname : "(null)", display_num);

        data = g_new0 (RemoveHostData, 1);
        data->hostname = hostname;
        data->display_num = display_num;
        gdm_display_store_foreach_remove (store,
                                          (GdmDisplayStoreFunc)remove_host,
                                          data);
        g_free (data);

        gdm_xdmcp_recount_sessions (factory);
}

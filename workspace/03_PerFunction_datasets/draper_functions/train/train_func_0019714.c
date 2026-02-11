on_device_treeview_row_activate (GtkMenuItem *menuitem,
                                 gpointer     user_data)
{
        GUPnPServiceProxy         *proxy;
        GUPnPServiceIntrospection *introspection;


        proxy = get_selected_service ();
        if (proxy != NULL) {
                gboolean subscribed;

                subscribed = gupnp_service_proxy_get_subscribed (proxy);
                gupnp_service_proxy_set_subscribed (proxy, !subscribed);
        } else {
                GUPnPServiceActionInfo *action_info;


                action_info = get_selected_action (&proxy, &introspection);
                if (action_info != NULL) {
                        run_action_dialog (action_info,
                                           proxy,
                                           introspection);
                        g_object_unref (introspection);
                }
        }

        if (proxy != NULL)
                g_object_unref (proxy);
}

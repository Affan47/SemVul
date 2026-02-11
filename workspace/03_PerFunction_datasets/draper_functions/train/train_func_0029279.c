on_provider_new (GObject *source,
                 GAsyncResult *result,
                 gpointer user_data)
{
        GSimpleAsyncResult *async = G_SIMPLE_ASYNC_RESULT (user_data);
        NewClosure *closure = g_simple_async_result_get_op_res_gpointer (async);
        GError *error = NULL;
        UmRealmProvider *provider;

        provider = um_realm_provider_proxy_new_finish (result, &error);
        closure->manager->provider = provider;

        if (error == NULL) {
                g_dbus_proxy_set_default_timeout (G_DBUS_PROXY (closure->manager->provider), -1);
                g_debug ("Created realm manager");
        } else {
                g_simple_async_result_take_error (async, error);
        }
        g_simple_async_result_complete (async);

        g_object_unref (async);
}

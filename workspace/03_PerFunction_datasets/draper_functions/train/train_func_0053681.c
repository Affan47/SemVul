gupnp_service_proxy_cancel_action (GUPnPServiceProxy       *proxy,
                                   GUPnPServiceProxyAction *action)
{
        GUPnPContext *context;
        SoupSession *session;

        g_return_if_fail (GUPNP_IS_SERVICE_PROXY (proxy));
        g_return_if_fail (action);
        g_return_if_fail (proxy == action->proxy);

        if (action->msg != NULL) {
                context = gupnp_service_info_get_context
                                        (GUPNP_SERVICE_INFO (proxy));
                session = gupnp_context_get_session (context);

                soup_session_cancel_message (session,
                                             action->msg,
                                             SOUP_STATUS_CANCELLED);
        }

        if (action->error != NULL)
                g_error_free (action->error);

        gupnp_service_proxy_action_free (action);
}

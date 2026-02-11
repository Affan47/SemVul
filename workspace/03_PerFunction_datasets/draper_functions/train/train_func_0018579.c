gupnp_service_proxy_end_action_hash (GUPnPServiceProxy       *proxy,
                                     GUPnPServiceProxyAction *action,
                                     GError                 **error,
                                     GHashTable              *hash)
{
        xmlDoc *response;
        xmlNode *params;

        g_return_val_if_fail (GUPNP_IS_SERVICE_PROXY (proxy), FALSE);
        g_return_val_if_fail (action, FALSE);
        g_return_val_if_fail (proxy == action->proxy, FALSE);


        if (action->error) {
                if (error)
                        *error = action->error;
                else
                        g_error_free (action->error);

                gupnp_service_proxy_action_free (action);

                return FALSE;
        }


        response = check_action_response (proxy, action, &params, error);
        if (response == NULL) {
                gupnp_service_proxy_action_free (action);

                return FALSE;
        }


        g_hash_table_foreach (hash, (GHFunc) read_out_parameter, params);


        gupnp_service_proxy_action_free (action);

        xmlFreeDoc (response);

        return TRUE;
}

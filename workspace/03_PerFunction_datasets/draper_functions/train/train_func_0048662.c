gssdp_client_get_property (GObject    *object,
                           guint       property_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
        GSSDPClient *client;

        client = GSSDP_CLIENT (object);

        switch (property_id) {
        case PROP_SERVER_ID:
                g_value_set_string
                        (value,
                         gssdp_client_get_server_id (client));
                break;
        case PROP_MAIN_CONTEXT:
                g_warning ("GSSDPClient:main-context is deprecated."
                           " Please use g_main_context_push_thread_default()");
                g_value_set_pointer
                        (value,
                         (gpointer)
                          g_main_context_get_thread_default ());
                break;
        case PROP_IFACE:
                g_value_set_string (value,
                                    gssdp_client_get_interface (client));
                break;
        case PROP_NETWORK:
                g_value_set_string (value,
                                    gssdp_client_get_network (client));
                break;
        case PROP_HOST_IP:
                g_value_set_string (value,
                                    gssdp_client_get_host_ip (client));
                break;
        case PROP_ACTIVE:
                g_value_set_boolean (value, client->priv->active);
                break;
        case PROP_SOCKET_TTL:
                g_value_set_uint (value, client->priv->socket_ttl);
                break;
        case PROP_MSEARCH_PORT:
                g_value_set_uint (value, client->priv->msearch_port);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}

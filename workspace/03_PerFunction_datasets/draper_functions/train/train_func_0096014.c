ga_client_get_property(GObject * object,
                       guint property_id,
                       GValue * value, GParamSpec * pspec) {
    GaClient *client = GA_CLIENT(object);
    GaClientPrivate *priv = GA_CLIENT_GET_PRIVATE(client);

    switch (property_id) {
        case PROP_STATE:
            g_value_set_enum(value, priv->state);
            break;
        case PROP_FLAGS:
            g_value_set_enum(value, priv->flags);
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

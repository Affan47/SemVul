set_property (GObject      *object,
              guint         prop_id,
              const GValue *value,
              GParamSpec   *pspec)
{
    GstCutterServerPrivate *priv = GST_CUTTER_SERVER_GET_PRIVATE(object);

    switch (prop_id) {
      case ARG_TEST_DIRECTORY:
        priv->test_directory = g_value_dup_string(value);
        break;
      case ARG_HOST:
        priv->host = g_value_dup_string(value);
        break;
      case ARG_PORT:
        priv->port = g_value_get_int(value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

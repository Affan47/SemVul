get_property (GObject    *object,
              guint       prop_id,
              GValue     *value,
              GParamSpec *pspec)
{
    CutTestDataPrivate *priv = CUT_TEST_DATA_GET_PRIVATE(object);

    switch (prop_id) {
      case PROP_NAME:
        g_value_set_string(value, priv->name);
        break;
      case PROP_VALUE:
        g_value_set_pointer(value, priv->value);
        break;
      case PROP_DESTROY_FUNCTION:
        g_value_set_pointer(value, priv->destroy_function);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

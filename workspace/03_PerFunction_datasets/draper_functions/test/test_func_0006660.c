get_property (GObject    *object,
              guint       prop_id,
              GValue     *value,
              GParamSpec *pspec)
{
    GstCutterConsoleOutputPrivate *priv;

    priv = GST_CUTTER_CONSOLE_OUTPUT_GET_PRIVATE(object);
    switch (prop_id) {
      case ARG_USE_COLOR:
        g_value_set_boolean(value, priv->use_color);
        break;
      case ARG_VERBOSE_LEVEL:
        g_value_set_string(value, priv->verbose_level_string);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

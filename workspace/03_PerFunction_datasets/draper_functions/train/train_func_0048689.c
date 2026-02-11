set_property (GObject      *object,
              guint         prop_id,
              const GValue *value,
              GParamSpec   *pspec)
{
    CutCairoPieChartPrivate *priv = CUT_CAIRO_PIE_CHART_GET_PRIVATE(object);

    switch (prop_id) {
      case PROP_WIDTH:
        priv->width = g_value_get_double(value);
        break;
      case PROP_HEIGHT:
        priv->height = g_value_get_double(value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

glade_property_set_real_property (GObject * object,
                                  guint prop_id,
                                  const GValue * value, GParamSpec * pspec)
{
  GladeProperty *property = GLADE_PROPERTY (object);

  switch (prop_id)
    {
      case PROP_CLASS:
        property->priv->klass = g_value_get_pointer (value);
        break;
      case PROP_ENABLED:
        glade_property_set_enabled (property, g_value_get_boolean (value));
        break;
      case PROP_SENSITIVE:
        property->priv->sensitive = g_value_get_boolean (value);
        break;
      case PROP_I18N_TRANSLATABLE:
        glade_property_i18n_set_translatable (property,
                                              g_value_get_boolean (value));
        break;
      case PROP_I18N_CONTEXT:
        glade_property_i18n_set_context (property, g_value_get_string (value));
        break;
      case PROP_I18N_COMMENT:
        glade_property_i18n_set_comment (property, g_value_get_string (value));
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

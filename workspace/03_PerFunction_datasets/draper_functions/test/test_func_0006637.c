peas_gtk_plugin_manager_view_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec)
{
  PeasGtkPluginManagerView *view = PEAS_GTK_PLUGIN_MANAGER_VIEW (object);

  switch (prop_id)
    {
    case PROP_ENGINE:
      view->priv->engine = g_value_get_object (value);
      break;
    case PROP_SHOW_BUILTIN:
      peas_gtk_plugin_manager_view_set_show_builtin (view,
                                                     g_value_get_boolean (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

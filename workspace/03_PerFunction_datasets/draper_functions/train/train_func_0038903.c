peas_gtk_plugin_manager_view_get_property (GObject    *object,
                                           guint       prop_id,
                                           GValue     *value,
                                           GParamSpec *pspec)
{
  PeasGtkPluginManagerView *view = PEAS_GTK_PLUGIN_MANAGER_VIEW (object);

  switch (prop_id)
    {
    case PROP_ENGINE:
      g_value_set_object (value, view->priv->engine);
      break;
    case PROP_SHOW_BUILTIN:
      g_value_set_boolean (value,
                           peas_gtk_plugin_manager_view_get_show_builtin (view));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

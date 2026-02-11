peas_gtk_plugin_manager_store_dispose (GObject *object)
{
  PeasGtkPluginManagerStore *store = PEAS_GTK_PLUGIN_MANAGER_STORE (object);

  if (store->priv->engine != NULL)
    {
      g_signal_handlers_disconnect_by_func (store->priv->engine,
                                            plugin_loaded_toggled_cb,
                                            store);
      g_clear_object (&store->priv->engine);
    }

  G_OBJECT_CLASS (peas_gtk_plugin_manager_store_parent_class)->dispose (object);
}

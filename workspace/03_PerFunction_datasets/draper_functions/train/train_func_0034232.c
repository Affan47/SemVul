peas_extension_set_constructed (GObject *object)
{
  PeasExtensionSet *set = PEAS_EXTENSION_SET (object);
  GList *plugins, *l;

  if (set->priv->engine == NULL)
    set->priv->engine = peas_engine_get_default ();

  g_object_ref (set->priv->engine);

  plugins = (GList *) peas_engine_get_plugin_list (set->priv->engine);
  for (l = plugins; l; l = l->next)
    add_extension (set, (PeasPluginInfo *) l->data);

  set->priv->load_handler_id =
          g_signal_connect_data (set->priv->engine, "load-plugin",
                                 G_CALLBACK (add_extension), set,
                                 NULL, G_CONNECT_AFTER | G_CONNECT_SWAPPED);
  set->priv->unload_handler_id =
          g_signal_connect_data (set->priv->engine, "unload-plugin",
                                 G_CALLBACK (remove_extension), set,
                                 NULL, G_CONNECT_SWAPPED);

  G_OBJECT_CLASS (peas_extension_set_parent_class)->constructed (object);
}

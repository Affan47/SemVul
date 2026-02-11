peas_gtk_plugin_manager_constructed (GObject *object)
{
  PeasGtkPluginManager *pm = PEAS_GTK_PLUGIN_MANAGER (object);
  GtkTreeSelection *selection;

  if (pm->priv->engine == NULL)
    pm->priv->engine = peas_engine_get_default ();

  g_object_ref (pm->priv->engine);


  peas_engine_rescan_plugins (pm->priv->engine);


  if (pm->priv->view != NULL)
    {
      PeasEngine *engine;

      g_object_get (pm->priv->view,
                    "engine", &engine,
                    NULL);

      g_warn_if_fail (engine == pm->priv->engine);

      if (engine != pm->priv->engine)
        g_clear_object (&pm->priv->view);

      g_object_unref (engine);
    }

  if (pm->priv->view == NULL)
    pm->priv->view = peas_gtk_plugin_manager_view_new (pm->priv->engine);

  gtk_widget_push_composite_child ();
  gtk_container_add (GTK_CONTAINER (pm->priv->sw), pm->priv->view);
  gtk_widget_pop_composite_child ();

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (pm->priv->view));

  g_signal_connect_swapped (selection,
                            "changed",
                            G_CALLBACK (selection_changed_cb),
                            pm);
  g_signal_connect_swapped (pm->priv->view,
                            "cursor-changed",
                            G_CALLBACK (selection_changed_cb),
                            pm);
  g_signal_connect (pm->priv->view,
                    "populate-popup",
                    G_CALLBACK (populate_popup_cb),
                    pm);
  g_signal_connect_after (pm->priv->engine,
                          "load-plugin",
                          G_CALLBACK (plugin_loaded_toggled_cb),
                          pm);
  g_signal_connect_after (pm->priv->engine,
                          "unload-plugin",
                          G_CALLBACK (plugin_loaded_toggled_cb),
                          pm);


  selection_changed_cb (pm);

  G_OBJECT_CLASS (peas_gtk_plugin_manager_parent_class)->constructed (object);
}

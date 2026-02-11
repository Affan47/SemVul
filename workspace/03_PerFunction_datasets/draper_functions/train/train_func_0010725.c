egg_toolbar_editor_set_model (EggToolbarEditor *t,
			      EggToolbarsModel *model)
{
  EggToolbarEditorPrivate *priv;

  g_return_if_fail (EGG_IS_TOOLBAR_EDITOR (t));
  g_return_if_fail (model != NULL);

  priv = t->priv;

  if (priv->model)
    {
      if (G_UNLIKELY (priv->model == model)) return;

      egg_toolbar_editor_disconnect_model (t);
      g_object_unref (priv->model);
    }

  priv->model = g_object_ref (model);

  update_editor_sheet (t);

  priv->sig_handlers[SIGNAL_HANDLER_ITEM_ADDED] =
    g_signal_connect_object (model, "item_added",
			     G_CALLBACK (item_added_or_removed_cb), t, 0);
  priv->sig_handlers[SIGNAL_HANDLER_ITEM_REMOVED] =
    g_signal_connect_object (model, "item_removed",
			     G_CALLBACK (item_added_or_removed_cb), t, 0);
  priv->sig_handlers[SIGNAL_HANDLER_TOOLBAR_REMOVED] =
    g_signal_connect_object (model, "toolbar_removed",
			     G_CALLBACK (toolbar_removed_cb), t, 0);
}

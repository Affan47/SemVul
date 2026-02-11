clear_menus (PlacemarksPlugin *plugin)
{
  GtkUIManager *manager;
  PlacemarksPluginPrivate *priv;
  GtkTreeIter iter;

  priv = PLACEMARKS_PLUGIN (plugin)->priv;
  manager = emerillon_window_get_ui_manager (priv->window);

  if (gtk_tree_model_get_iter_first (priv->model, &iter))
    {
      do
        {
          guint ui_id;

          gtk_tree_model_get (priv->model, &iter, COL_UI_ID, &ui_id, -1);
          gtk_ui_manager_remove_ui (manager, ui_id);
        }
      while (gtk_tree_model_iter_next (priv->model, &iter));
    }

  gtk_ui_manager_remove_action_group (manager,
                                      priv->menu_action_group);

  return FALSE;
}

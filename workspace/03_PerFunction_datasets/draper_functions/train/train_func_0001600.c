_show_add_to_group_dialog_on_idle (GSList *pictures)
{
  FrogrController *controller = NULL;
  FrogrControllerPrivate *priv = NULL;
  FrogrModel *model = NULL;
  GSList *groups = NULL;

  controller = frogr_controller_get_instance ();
  priv = FROGR_CONTROLLER_GET_PRIVATE (controller);


  if (priv->fetching_groups)
      return G_SOURCE_CONTINUE;

  model = frogr_main_view_get_model (priv->mainview);
  groups = frogr_model_get_groups (model);

  if (frogr_model_n_groups (model) > 0)
    frogr_add_to_group_dialog_show (GTK_WINDOW (priv->mainview), pictures, groups);
  else if (priv->groups_fetched)
    frogr_util_show_info_dialog (GTK_WINDOW (priv->mainview), _("No groups found"));

  priv->show_add_to_group_dialog_source_id = 0;
  return G_SOURCE_REMOVE;
}

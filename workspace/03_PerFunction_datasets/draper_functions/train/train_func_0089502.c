clear_dest_info (ExoIconView *icon_view)
{
  if (icon_view->priv->dest_targets)
    gtk_target_list_unref (icon_view->priv->dest_targets);
  icon_view->priv->dest_targets = NULL;

  icon_view->priv->dest_set = FALSE;
}

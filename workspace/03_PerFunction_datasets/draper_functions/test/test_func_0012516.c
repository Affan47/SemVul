wnck_pager_init (WnckPager *pager)
{
  int i;
  static const GtkTargetEntry targets[] = {
    { "application/x-wnck-window-id", 0, 0}
  };

  pager->priv = WNCK_PAGER_GET_PRIVATE (pager);

  pager->priv->n_rows = 1;
  pager->priv->display_mode = WNCK_PAGER_DISPLAY_CONTENT;
  pager->priv->show_all_workspaces = TRUE;
  pager->priv->shadow_type = GTK_SHADOW_NONE;

  pager->priv->orientation = GTK_ORIENTATION_HORIZONTAL;
  pager->priv->workspace_size = 48;

  for (i = 0; i < N_SCREEN_CONNECTIONS; i++)
    pager->priv->screen_connections[i] = 0;

  pager->priv->prelight = -1;

  pager->priv->layout_manager_token = WNCK_NO_MANAGER_TOKEN;

  g_object_set (pager, "has-tooltip", TRUE, NULL);

  gtk_drag_dest_set (GTK_WIDGET (pager), 0, targets, G_N_ELEMENTS (targets), GDK_ACTION_MOVE);
  gtk_widget_set_can_focus (GTK_WIDGET (pager), TRUE);
}

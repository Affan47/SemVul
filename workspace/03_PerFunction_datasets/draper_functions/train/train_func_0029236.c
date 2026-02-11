do_dispose (GObject *obj)
{
  TpawAccountWidget *self = TPAW_ACCOUNT_WIDGET (obj);

  g_clear_object (&self->priv->settings);
  g_clear_object (&self->priv->account_manager);
  g_clear_object (&self->priv->action_area);

  if (G_OBJECT_CLASS (tpaw_account_widget_parent_class)->dispose != NULL)
    G_OBJECT_CLASS (tpaw_account_widget_parent_class)->dispose (obj);
}

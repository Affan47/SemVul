unset_fixed_style (EggEditableToolbar *t)
{
  g_return_if_fail (GTK_IS_TOOLBAR (t->priv->fixed_toolbar));
  gtk_toolbar_unset_style (GTK_TOOLBAR (t->priv->fixed_toolbar));
}

set_fixed_style (EggEditableToolbar *t, GtkToolbarStyle style)
{
  g_return_if_fail (GTK_IS_TOOLBAR (t->priv->fixed_toolbar));
  gtk_toolbar_set_style (GTK_TOOLBAR (t->priv->fixed_toolbar),
  			 style == GTK_TOOLBAR_ICONS ? GTK_TOOLBAR_BOTH_HORIZ : style);
}

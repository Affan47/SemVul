egg_editable_toolbar_set_fixed (EggEditableToolbar *etoolbar,
				GtkToolbar *toolbar)
{
  EggEditableToolbarPrivate *priv = etoolbar->priv;

  g_return_if_fail (!toolbar || GTK_IS_TOOLBAR (toolbar));

  if (priv->fixed_toolbar)
    {
      unparent_fixed (etoolbar);
      g_object_unref (priv->fixed_toolbar);
      priv->fixed_toolbar = NULL;
    }

  if (toolbar)
    {
      priv->fixed_toolbar = GTK_WIDGET (toolbar);
      gtk_toolbar_set_show_arrow (toolbar, FALSE);
      g_object_ref_sink (toolbar);
    }

  update_fixed (etoolbar);
}

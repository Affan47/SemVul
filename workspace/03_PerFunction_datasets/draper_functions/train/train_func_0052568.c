glade_design_layout_unrealize (GtkWidget * widget)
{
  GladeDesignLayoutPrivate *priv;
  gint i;

  priv = GLADE_DESIGN_LAYOUT_PRIVATE (widget);

  if (priv->offscreen_window)
    {
      gdk_window_set_user_data (priv->offscreen_window, NULL);
      gdk_window_destroy (priv->offscreen_window);
      priv->offscreen_window = NULL;
    }


  for (i = 0; i < N_ACTIVITY; i++)
    {
      if (priv->cursors[i])
        {
          g_object_unref (priv->cursors[i]);
          priv->cursors[i] = NULL;
        }
    }

  priv->cursor = NULL;

  if (priv->widget_name)
    {
      g_object_unref (priv->widget_name);
      priv->widget_name = NULL;
    }

  GTK_WIDGET_CLASS (glade_design_layout_parent_class)->unrealize (widget);
}

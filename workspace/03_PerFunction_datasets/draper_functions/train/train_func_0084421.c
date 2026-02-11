exo_icon_bar_set_adjustments (ExoIconBar    *icon_bar,
                              GtkAdjustment *hadj,
                              GtkAdjustment *vadj)
{
  gboolean need_adjust = FALSE;

  if (hadj != NULL)
    g_return_if_fail (GTK_IS_ADJUSTMENT (hadj));
  else
    hadj = GTK_ADJUSTMENT (gtk_adjustment_new (0.0, 0.0, 0.0, 0.0, 0.0, 0.0));

  if (vadj != NULL)
    g_return_if_fail (GTK_IS_ADJUSTMENT (vadj));
  else
    vadj = GTK_ADJUSTMENT (gtk_adjustment_new (0.0, 0.0, 0.0, 0.0, 0.0, 0.0));

  if (icon_bar->priv->hadjustment && (icon_bar->priv->hadjustment != hadj))
    {
      g_signal_handlers_disconnect_matched (icon_bar->priv->hadjustment, G_SIGNAL_MATCH_DATA,
                                            0, 0, NULL, NULL, icon_bar);
      g_object_unref (icon_bar->priv->hadjustment);
    }

  if (icon_bar->priv->vadjustment && (icon_bar->priv->vadjustment != vadj))
    {
      g_signal_handlers_disconnect_matched (icon_bar->priv->vadjustment, G_SIGNAL_MATCH_DATA,
                                            0, 0, NULL, NULL, icon_bar);
      g_object_unref (icon_bar->priv->vadjustment);
    }

  if (icon_bar->priv->hadjustment != hadj)
    {
      icon_bar->priv->hadjustment = hadj;
      g_object_ref (icon_bar->priv->hadjustment);
      gtk_object_sink (GTK_OBJECT (icon_bar->priv->hadjustment));

      g_signal_connect (icon_bar->priv->hadjustment, "value_changed",
                        G_CALLBACK (exo_icon_bar_adjustment_changed), icon_bar);
      need_adjust = TRUE;
    }

  if (icon_bar->priv->vadjustment != vadj)
    {
      icon_bar->priv->vadjustment = vadj;
      g_object_ref (icon_bar->priv->vadjustment);
      gtk_object_sink (GTK_OBJECT (icon_bar->priv->vadjustment));

      g_signal_connect (icon_bar->priv->vadjustment, "value_changed",
                        G_CALLBACK (exo_icon_bar_adjustment_changed), icon_bar);
      need_adjust = TRUE;
    }

  if (need_adjust)
    exo_icon_bar_adjustment_changed (NULL, icon_bar);
}

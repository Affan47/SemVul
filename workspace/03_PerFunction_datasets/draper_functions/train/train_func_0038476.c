stats_dialog_response_cb (GtkWidget *widget,
                          int response,
                          AisleriotWindow *window)
{
  AisleriotWindowPrivate *priv = window->priv;

  if (response == GTK_RESPONSE_REJECT) {
    AisleriotStatistic current_stats = { 0, 0, 0, 0 };

    aisleriot_conf_set_statistic (aisleriot_game_get_game_module (priv->game),
                                  &current_stats);
    aisleriot_stats_dialog_update (priv->stats_dialog, &current_stats);

    return;
  }

  gtk_widget_destroy (widget);
}

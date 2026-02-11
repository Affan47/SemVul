show_game_over_dialog (AisleriotWindow *window)
{
  AisleriotWindowPrivate *priv = window->priv;
  GtkWidget *dialog;
  const char *message;
  gboolean game_won;

  game_won = aisleriot_game_get_state (priv->game) == GAME_WON;

  if (game_won) {
    message = _("Congratulations, you have won!");
    ar_sound_play ("victory");

  } else {
    message =  _("There are no more moves");
    ar_sound_play ("splat");
  }

  dialog = gtk_message_dialog_new_with_markup (GTK_WINDOW (window),
					       GTK_DIALOG_DESTROY_WITH_PARENT,
					       GTK_MESSAGE_INFO,
					       GTK_BUTTONS_NONE,
                                               "<b>%s</b>",
                                               message);

  gtk_window_set_title (GTK_WINDOW (dialog), "");
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);

  if (game_won) {
    gtk_dialog_add_buttons (GTK_DIALOG (dialog),
                            GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE,
                            AR_STOCK_START_NEW_GAME, RESPONSE_NEW_GAME,
                            NULL);
    gtk_dialog_set_alternative_button_order (GTK_DIALOG (dialog),
                                             RESPONSE_NEW_GAME,
                                             GTK_RESPONSE_CLOSE,
                                             -1);
  } else {
    gtk_dialog_add_buttons (GTK_DIALOG (dialog),
			    AR_STOCK_UNDO_MOVE, RESPONSE_UNDO,
                            GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE,
                            AR_STOCK_RESTART_GAME, RESPONSE_RESTART,
                            AR_STOCK_START_NEW_GAME, RESPONSE_NEW_GAME,
                            NULL);
    gtk_dialog_set_alternative_button_order (GTK_DIALOG (dialog),
                                             RESPONSE_NEW_GAME,
                                             RESPONSE_RESTART,
                                             GTK_RESPONSE_CLOSE,
                                             RESPONSE_UNDO,
                                             -1);
  }

  gtk_dialog_set_default_response (GTK_DIALOG (dialog), RESPONSE_NEW_GAME);

  priv->game_over_dialog = dialog;
  g_signal_connect (dialog, "response",
                    G_CALLBACK (game_over_dialog_response_cb), window);
  g_signal_connect (dialog, "destroy",
                    G_CALLBACK (gtk_widget_destroyed), &priv->game_over_dialog);

  gtk_widget_show (dialog);
}

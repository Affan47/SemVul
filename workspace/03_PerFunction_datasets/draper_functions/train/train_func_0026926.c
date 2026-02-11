do_setup (GtkWidget * widget, gpointer data)
{
  const gchar  *type_name = NULL;
  int i;
  char **player_names;
  gsize n_player_names;

  NumberOfComputers =
    gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (ComputerSpinner));
  NumberOfHumans =
    gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (HumanSpinner));

  if (tmpDoDelay == -1)
    tmpDoDelay = DoDelay;
  else
    DoDelay = tmpDoDelay;

  DisplayComputerThoughts = tmpDisplayComputerThoughts;

  for (i = 0; i < MAX_NUMBER_OF_PLAYERS; i++) {
    if (players[i].name != _(DefaultPlayerNames[i]))
      g_free (players[i].name);
    players[i].name =
      g_strdup (gtk_entry_get_text (GTK_ENTRY (PlayerNames[i])));

    if (i < NumberOfPlayers)
      score_list_set_column_title (ScoreList, i + 1, players[i].name);
  }

  setupdialog_destroy (setupdialog, 1);

  n_player_names = MAX_NUMBER_OF_PLAYERS;
  player_names = g_newa (char *, n_player_names + 1);
  for (i = 0; i < MAX_NUMBER_OF_PLAYERS; ++i) {
    player_names[i] = players[i].name;
  }
  player_names[i] = NULL;

  g_settings_set_strv (settings, "player-names", (const gchar *const *) player_names);

  g_settings_set_int (settings, "number-of-computer-opponents", NumberOfComputers);

  g_settings_set_int (settings, "number-of-human-opponents", NumberOfHumans);

  g_settings_set_boolean (settings, "delay-between-rolls", DoDelay);

  type_name = game_type_name(NewGameType);
  if (type_name) {
    g_settings_set_string (settings, "game-type", type_name);
  }

  g_settings_set_int (settings, "monte-carlo-trials", NUM_TRIALS);

  if (((NumberOfComputers != OriginalNumberOfComputers)
       || (NumberOfHumans != OriginalNumberOfHumans)
       || (NewGameType != game_type))
      && !GameIsOver ())
    WarnNumPlayersChanged ();
}

fill_typemenu (GtkWidget * menu)
{
  gint i;
  gchar *config;

  for (i = 0; i < num_game_configs (); ++i) {
    config = game_config_name (i);
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (menu), _(config));
    g_free (config);
  }

  gtk_combo_box_set_active (GTK_COMBO_BOX (menu), properties.selected_config);
}

gc_board_conf_boolean_box_toggled (GtkToggleButton *togglebutton,
			      gpointer key)
{
  _gc_boardconf_key *u = (_gc_boardconf_key*)key;
  gchar *the_key = g_strdup(u->key);
  gchar *value;

  if (gtk_toggle_button_get_active (togglebutton))
    value = g_strdup("True");
  else
    value = g_strdup("False");

  g_hash_table_replace(u->config->hash_conf, (gpointer) the_key, (gpointer) value);
}

science_report_goal_callback(GtkComboBox *combo, gpointer data)
{
  Tech_type_id tech;
  const char *tech_name;

  if (!science_report_combo_get_active(combo, &tech, &tech_name)) {
    return;
  }

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data))) {
    popup_help_dialog_typed(tech_name, HELP_TECH);
  } else if (can_client_issue_orders()) {
    dsend_packet_player_tech_goal(&client.conn, tech);
  }

  science_report_combo_set_active(combo, player_research_get
                                  (client_player())->tech_goal);
}

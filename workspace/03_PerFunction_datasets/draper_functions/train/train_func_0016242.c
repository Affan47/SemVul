races_response(GtkWidget *w, gint response, gpointer data)
{
  if (response == GTK_RESPONSE_ACCEPT) {
    const char *s;


    if (selected_nation == -1) {
      return;
    }

    if (selected_sex == -1) {
      output_window_append(ftc_client, _("You must select your sex."));
      return;
    }

    if (selected_city_style == -1) {
      output_window_append(ftc_client, _("You must select your city style."));
      return;
    }

    s = gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(races_leader))));


    if (strlen(s) == 0) {
      output_window_append(ftc_client, _("You must type a legal name."));
      return;
    }

    dsend_packet_nation_select_req(&client.conn,
				   player_number(races_player), selected_nation,
				   selected_sex, s, selected_city_style);
  } else if (response == GTK_RESPONSE_NO) {
    dsend_packet_nation_select_req(&client.conn,
				   player_number(races_player),
				   -1, FALSE, "", 0);
  }

  popdown_races_dialog();
}

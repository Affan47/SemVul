show_conn_popup(struct player *pplayer, struct connection *pconn)
{
  GtkWidget *popup;
  char buf[1024] = "";

  if (pconn) {
    cat_snprintf(buf, sizeof(buf), _("Connection name: %s"),
                 pconn->username);
  } else {
    cat_snprintf(buf, sizeof(buf), _("Player name: %s"),
                 player_name(pplayer));
  }
  cat_snprintf(buf, sizeof(buf), "\n");
  if (pconn) {
    cat_snprintf(buf, sizeof(buf), _("Host: %s"), pconn->addr);
  }
  cat_snprintf(buf, sizeof(buf), "\n");


  popup = gtk_message_dialog_new(NULL, 0,
				 GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
				 "%s", buf);
  gtk_window_set_title(GTK_WINDOW(popup), _("Player/conn info"));
  setup_dialog(popup, toplevel);
  g_signal_connect(popup, "response", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_window_present(GTK_WINDOW(popup));
}

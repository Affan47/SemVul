popup_upgrade_dialog(struct unit_list *punits)
{
  GtkWidget *shell;
  char buf[512];

  if (!punits || unit_list_size(punits) == 0) {
    return;
  }

  if (!get_units_upgrade_info(buf, sizeof(buf), punits)) {
    shell = gtk_message_dialog_new(NULL, 0,
				   GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
				   "%s", buf);
    gtk_window_set_title(GTK_WINDOW(shell), _("Upgrade Unit!"));
    setup_dialog(shell, toplevel);
    g_signal_connect(shell, "response", G_CALLBACK(gtk_widget_destroy),
                    NULL);
    gtk_window_present(GTK_WINDOW(shell));
  } else {
    shell = gtk_message_dialog_new(NULL, 0,
				   GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
				   "%s", buf);
    gtk_window_set_title(GTK_WINDOW(shell), _("Upgrade Obsolete Units"));
    setup_dialog(shell, toplevel);
    gtk_dialog_set_default_response(GTK_DIALOG(shell), GTK_RESPONSE_YES);

    if (gtk_dialog_run(GTK_DIALOG(shell)) == GTK_RESPONSE_YES) {
      unit_list_iterate(punits, punit) {
	request_unit_upgrade(punit);
      } unit_list_iterate_end;
    }
    gtk_widget_destroy(shell);
  }
}

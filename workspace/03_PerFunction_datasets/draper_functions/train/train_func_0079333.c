ask_for_auth_info(const string &msg, bool echo)
{
  const char *failed;
  char *reply, *local;
  int result;

  GtkWidget *dialog, *entry;
  GdkGrabStatus status;

  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
				  GTK_MESSAGE_QUESTION,
				  GTK_BUTTONS_OK_CANCEL,
				  "%s",
				  msg.c_str());

  entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(gtk_message_dialog_get_message_area(GTK_MESSAGE_DIALOG(dialog))), entry, FALSE,
		     FALSE, 0);
  if(!echo)
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
  gtk_widget_grab_focus(entry);
  gtk_widget_show(entry);

  gtk_window_set_title(GTK_WINDOW(dialog), "Upgrade notification");
  gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);


  gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
  g_signal_connect(G_OBJECT(entry), "activate",
		   G_CALLBACK(root_slave_ok), dialog);


  gtk_widget_show_now(dialog);

  status = gdk_keyboard_grab(gtk_widget_get_parent_window(dialog), FALSE,
			     GDK_CURRENT_TIME);

  if (status != GDK_GRAB_SUCCESS)
    {
      failed = "keyboard";


      gdk_pointer_ungrab(GDK_CURRENT_TIME);

      gtk_widget_destroy(dialog);

      report_failed_grab(failed);
    }
  else
    {
      result = gtk_dialog_run(GTK_DIALOG(dialog));

      gdk_keyboard_ungrab(GDK_CURRENT_TIME);
      gdk_flush();


      reply = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
      if (result == GTK_RESPONSE_OK) {
	string::size_type s=strlen(reply);

	GError *err=NULL;

	local = NULL;

	local = g_locale_from_utf8(reply, s,
				   NULL, NULL, &err);

	handle_gerror("Unable to convert input from UTF8: %s",
		      &err);

	if (local != NULL) {
	  s=strlen(local);
	  write_msgid(to_slave, APPLET_CMD_AUTHREPLY);
	  write(to_slave, &s, sizeof(s));
	  write(to_slave, local, s);

	  memset(local, '\0', strlen(local));
	  g_free(local);
	} else {
	  write_msgid(to_slave, APPLET_CMD_AUTHREPLY);
	  write(to_slave, &s, sizeof(s));
	  write(to_slave, reply, s);
	}

	s=0;
      }


      memset(reply, '\b', strlen(reply));
      gtk_entry_set_text(GTK_ENTRY(entry), reply);
      memset(reply, '\0', strlen(reply));
      g_free(reply);
      gtk_widget_destroy(dialog);
      return (result == GTK_RESPONSE_OK ? 0 : -1);
    }

  return (-1);

}

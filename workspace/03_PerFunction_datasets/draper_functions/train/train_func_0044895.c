first_run_check()
{

  gchar *rc_file = g_build_filename(g_get_user_config_dir(), PREFERENCES_FILE, NULL);

  if (!g_file_test(rc_file, G_FILE_TEST_EXISTS))
  {
    GtkWidget* confirm_dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_OTHER,
                                                       GTK_BUTTONS_YES_NO,
                                                       SAVE_HIST_MESSAGE);
    gtk_window_set_title((GtkWindow*)confirm_dialog, _("Save history"));

    if (gtk_dialog_run((GtkDialog*)confirm_dialog) == GTK_RESPONSE_YES)
    {
      prefs.save_history = TRUE;
    } else {
      prefs.save_history = FALSE;
    }
    gtk_widget_destroy(confirm_dialog);

    prefs.history_key = DEF_HISTORY_KEY;
    prefs.actions_key = DEF_ACTIONS_KEY;
    prefs.menu_key = DEF_MENU_KEY;
    prefs.search_key = DEF_SEARCH_KEY;
    prefs.offline_key = DEF_OFFLINE_KEY;
    save_preferences();
  }
  g_free(rc_file);
}

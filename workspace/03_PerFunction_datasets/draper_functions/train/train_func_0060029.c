set_base_dir  (  char *path ) {
    GtkWidget * dialog;
    struct stat stat_buf;


    if (stat (path, &stat_buf) != 0) {
      dialog = gtk_message_dialog_new(GTK_WINDOW(gjay->main_window),
          GTK_DIALOG_DESTROY_WITH_PARENT,
          GTK_MESSAGE_ERROR,
          GTK_BUTTONS_CLOSE,
          _("Error getting status of directory '%s': %s"),
          path, g_strerror(errno));
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
      return;
    }
    if (!S_ISDIR(stat_buf.st_mode)) {
      dialog = gtk_message_dialog_new(GTK_WINDOW(gjay->main_window),
          GTK_DIALOG_DESTROY_WITH_PARENT,
          GTK_MESSAGE_ERROR,
          GTK_BUTTONS_CLOSE,
          _("Path '%s' is not a directory."),
          path);
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
      return;
    }
    if (gjay->prefs->song_root_dir) {
        g_free(gjay->prefs->song_root_dir);


        send_ipc(ui_pipe_fd, CLEAR_ANALYSIS_QUEUE);
    }
    gjay->prefs->song_root_dir = g_strdup(path);
    prefs_update_song_dir();
    gtk_idle_add(explore_view_set_root_idle, NULL);

    set_add_files_progress(_("Scanning tree..."), 0);
    set_analysis_progress_visible(FALSE);
    set_add_files_progress_visible(TRUE);
}

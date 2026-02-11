gnac_on_converter_overwrite_cb(LibgnacConverter *converter,
                               GFile            *file,
                               gpointer          user_data)
{

  static gboolean overwrite = FALSE;

  if (remember_overwrite) return overwrite;

  GError *error = NULL;
  gchar *display_name = gnac_utils_get_display_name_from_file(file, &error);

  GtkWidget *dialog = gtk_message_dialog_new(
      GTK_WINDOW(gnac_ui_get_widget("main_window")),
      GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO,
      _("File %s already exists...\nOverwrite?"),
      display_name);
  g_free(display_name);
  gtk_window_set_title(GTK_WINDOW(dialog), PACKAGE_NAME);

  GtkWidget *checkbox = gtk_check_button_new_with_label(
      _("Remember my decision"));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), FALSE);
  gtk_box_pack_end(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
      checkbox, FALSE, FALSE, 0);
  gtk_widget_show(checkbox);

  gdk_threads_enter();
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
  gdk_threads_leave();

  remember_overwrite = gtk_toggle_button_get_active(
      GTK_TOGGLE_BUTTON(checkbox));

  gtk_widget_destroy(dialog);

  overwrite = (response == GTK_RESPONSE_YES);

  return overwrite;
}

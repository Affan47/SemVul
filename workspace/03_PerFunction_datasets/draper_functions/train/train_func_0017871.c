we_log_start_cb(GtkWidget *widget, gpointer data)
{
  World           *world = (World *) data;
  gint             lines = 0;
  gchar           *errmsg = NULL;
  GtkToggleButton *chkLogIncludePrevious;
  GtkSpinButton   *spnLogPreviousLines;


  update_we_logging_parameters(world, world->ui_builder);


  chkLogIncludePrevious
    = GTK_TOGGLE_BUTTON(gtk_builder_get_object(world->ui_builder, "chkLogIncludePrevious"));
  spnLogPreviousLines
    = GTK_SPIN_BUTTON(gtk_builder_get_object(world->ui_builder, "spnLogPreviousLines"));

  if (gtk_toggle_button_get_active(chkLogIncludePrevious)) {
    lines = (int) gtk_spin_button_get_value(spnLogPreviousLines);
  }

  if (start_log(world, lines, &errmsg)) {
    fill_we_logging_tab(world, world->ui_builder);
  } else {
    GtkWidget *msgdlg = gtk_message_dialog_new(GTK_WINDOW(world->dlgEditWorld),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_CLOSE,
                                               errmsg);
    gtk_window_set_title(GTK_WINDOW(msgdlg), _("Logging not started"));
    gtk_dialog_run(GTK_DIALOG(msgdlg));
    gtk_widget_destroy(msgdlg);
    g_free(errmsg);
  }
}

check_reload_project (GladeWindow *window, GladeProject *project)
{
  gchar *path;
  GtkWidget *dialog;
  GtkWidget *button;
  gint response;


  if ((glade_util_get_file_mtime (glade_project_get_path (project), NULL)
       <= glade_project_get_file_mtime (project)))
    {
      return;
    }

  if (glade_project_get_modified (project))
    {
      dialog = gtk_message_dialog_new (GTK_WINDOW (window),
                                       GTK_DIALOG_MODAL,
                                       GTK_MESSAGE_WARNING,
                                       GTK_BUTTONS_NONE,
                                       _("The project %s has unsaved changes"),
                                       glade_project_get_path (project));

      gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
                                                _
                                                ("If you reload it, all unsaved changes "
                                                 "could be lost. Reload it anyway?"));
    }
  else
    {
      dialog = gtk_message_dialog_new (GTK_WINDOW (window),
                                       GTK_DIALOG_MODAL,
                                       GTK_MESSAGE_WARNING,
                                       GTK_BUTTONS_NONE,
                                       _
                                       ("The project file %s has been externally modified"),
                                       glade_project_get_path (project));

      gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
                                                _
                                                ("Do you want to reload the project?"));

    }

  gtk_window_set_title (GTK_WINDOW (dialog), "");

  button = gtk_button_new_with_mnemonic (_("_Reload"));
  gtk_button_set_image (GTK_BUTTON (button),
                        gtk_image_new_from_stock (GTK_STOCK_REFRESH,
                                                  GTK_ICON_SIZE_BUTTON));
  gtk_widget_show (button);

  gtk_dialog_add_button (GTK_DIALOG (dialog), GTK_STOCK_CANCEL,
                         GTK_RESPONSE_REJECT);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog), button,
                                GTK_RESPONSE_ACCEPT);
  gtk_dialog_set_alternative_button_order (GTK_DIALOG (dialog),
                                           GTK_RESPONSE_ACCEPT,
                                           GTK_RESPONSE_REJECT, -1);


  gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_REJECT);

  response = gtk_dialog_run (GTK_DIALOG (dialog));

  gtk_widget_destroy (dialog);

  if (response == GTK_RESPONSE_REJECT)
    {
      return;
    }


  path = g_strdup (glade_project_get_path (project));

  do_close (window, project);
  open_project (window, path);
  g_free (path);
}

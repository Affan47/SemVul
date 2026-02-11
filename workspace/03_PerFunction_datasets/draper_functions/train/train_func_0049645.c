exo_die_editor_path_clicked (GtkWidget    *button,
                             ExoDieEditor *editor)
{
  GtkWidget *toplevel;
  GtkWidget *chooser;
  gchar     *path;

  g_return_if_fail (GTK_IS_BUTTON (button));
  g_return_if_fail (EXO_DIE_IS_EDITOR (editor));


  toplevel = gtk_widget_get_toplevel (button);
  if (toplevel == NULL || !GTK_WIDGET_TOPLEVEL (toplevel))
    return;


  chooser = gtk_file_chooser_dialog_new (_("Select a working directory"),
                                         GTK_WINDOW (toplevel),
                                         GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
                                         NULL);
  gtk_dialog_set_default_response (GTK_DIALOG (chooser), GTK_RESPONSE_ACCEPT);
  gtk_dialog_set_alternative_button_order (GTK_DIALOG (chooser),
                                           GTK_RESPONSE_ACCEPT,
                                           GTK_RESPONSE_CANCEL,
                                           -1);


  if (G_LIKELY (!exo_str_is_empty (editor->path)))
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser), editor->path);


  if (gtk_dialog_run (GTK_DIALOG (chooser)) == GTK_RESPONSE_ACCEPT)
    {

      path = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
      exo_die_editor_set_path (editor, path);
      g_free (path);
    }


  gtk_widget_destroy (chooser);
}

menu_open_ok (G_GNUC_UNUSED GtkWidget * widget, GtkFileSelection * filew)
{
  GtkWidget *dialog;
  const gchar *name;
  gchar *basename;
  FILE *file;

  name = gtk_file_selection_get_filename (GTK_FILE_SELECTION (filew));
  if (!g_file_test (name, G_FILE_TEST_IS_REGULAR))
    {
      dialog = gtk_message_dialog_new
	(GTK_WINDOW (filew), GTK_DIALOG_DESTROY_WITH_PARENT,
	 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, _("Cannot open file '%s'"),
	 name);
      gtk_dialog_run (GTK_DIALOG (dialog));
      gtk_widget_destroy (dialog);
      return;
    }

  file = fopen (name, "r");
  if (file == NULL)
    {
      dialog = gtk_message_dialog_new
	(GTK_WINDOW (filew), GTK_DIALOG_DESTROY_WITH_PARENT,
	 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, _("Cannot open file '%s'"),
	 name);
      gtk_dialog_run (GTK_DIALOG (dialog));
      gtk_widget_destroy (dialog);
      return;
    }

  init_everything ();
  bonds = load_list_bonds (file, 0, 0);
  adjust_all_atom_in_list (bonds, drawing_area, mode, zoom);

  if (bonds == NULL)
    {
      dialog = gtk_message_dialog_new
	(GTK_WINDOW (filew), GTK_DIALOG_DESTROY_WITH_PARENT,
	 GTK_MESSAGE_ERROR,
	 GTK_BUTTONS_CLOSE, _("File '%s' has incorrect format"), name);
      gtk_dialog_run (GTK_DIALOG (dialog));
      gtk_widget_destroy (dialog);
      return;
    }
  fclose (file);

  save_last_dlg_path (name);
  filename = g_strdup (name);
  basename = g_path_get_basename (name);
  gtk_window_set_title (GTK_WINDOW (window),
			g_strdup_printf ("EasyChem [%s]", basename));
  g_free (basename);

  gtk_object_destroy (GTK_OBJECT (filew));
  draw_bond_list (bonds, 0, 0, drawing_area, pixmap, mode, zoom);
}

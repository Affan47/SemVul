print_dialog_action_choosefile (GtkWidget * w, PrintDialog * dialog)
{
  GtkWidget *filechooser;
  const gchar *filename;
  const gchar *newfilename;
  filechooser = gtk_file_chooser_dialog_new (_("Select PostScript Filename..."),
					     GTK_WINDOW (dialog),
					     GTK_FILE_CHOOSER_ACTION_SAVE,
					     GTK_STOCK_CANCEL,
					     GTK_RESPONSE_CANCEL,
					     GTK_STOCK_OK,
					     GTK_RESPONSE_ACCEPT, NULL);


  gtk_dialog_set_alternative_button_order(GTK_DIALOG(filechooser),
					  GTK_RESPONSE_ACCEPT,
					  GTK_RESPONSE_CANCEL,
					  -1);

  filename = gtk_entry_get_text (GTK_ENTRY (dialog->fnfield));
  gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (filechooser), filename);

  gtk_dialog_set_default_response(GTK_DIALOG(filechooser),
				  GTK_RESPONSE_ACCEPT);

  if (gtk_dialog_run (GTK_DIALOG (filechooser)) == GTK_RESPONSE_ACCEPT)
    {
      newfilename =
	gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (filechooser));
      gtk_entry_set_text (GTK_ENTRY (dialog->fnfield), newfilename);
    }

  gtk_widget_destroy (filechooser);

}

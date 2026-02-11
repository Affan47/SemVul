exporter_categ ( GtkButton * widget, gpointer data )
{
    GtkWidget *dialog;
    gint resultat;
    gchar *nom_categ;

    dialog = gtk_file_chooser_dialog_new ( _("Export categories"),
					   GTK_WINDOW ( window ),
					   GTK_FILE_CHOOSER_ACTION_SAVE,
					   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					   GTK_STOCK_SAVE, GTK_RESPONSE_OK,
					   NULL);

    gtk_file_chooser_set_current_name ( GTK_FILE_CHOOSER ( dialog ),  _("Categories.cgsb"));
    gtk_file_chooser_set_current_folder ( GTK_FILE_CHOOSER ( dialog ), gsb_file_get_last_path () );
    gtk_file_chooser_set_do_overwrite_confirmation ( GTK_FILE_CHOOSER ( dialog ), TRUE);
    gtk_window_set_position ( GTK_WINDOW ( dialog ), GTK_WIN_POS_CENTER_ON_PARENT );

    resultat = gtk_dialog_run ( GTK_DIALOG ( dialog ));

    if ( resultat != GTK_RESPONSE_OK )
    {
	gtk_widget_destroy ( dialog );
	return FALSE;
    }

    nom_categ = file_selection_get_filename ( GTK_FILE_CHOOSER ( dialog ));
    gsb_file_update_last_path (file_selection_get_last_directory (GTK_FILE_CHOOSER (dialog), TRUE));
    gtk_widget_destroy ( GTK_WIDGET ( dialog ));

    gsb_file_others_save_category ( nom_categ );

    return FALSE;
}

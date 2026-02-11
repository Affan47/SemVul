modification_logo_accueil ( )
{
    GtkWidget *file_selector;
    GtkWidget *preview;

    file_selector = gtk_file_chooser_dialog_new ( _("Select a new logo"),
					   GTK_WINDOW ( fenetre_preferences ),
					   GTK_FILE_CHOOSER_ACTION_OPEN,
					   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					   GTK_STOCK_OPEN, GTK_RESPONSE_OK,
					   NULL);

    if ( etat.is_pixmaps_dir )
        gtk_file_chooser_set_current_folder ( GTK_FILE_CHOOSER (
                        file_selector ), GRISBI_PIXMAPS_DIR );
    else
        gtk_file_chooser_set_current_folder ( GTK_FILE_CHOOSER (
                        file_selector ), gsb_file_get_last_path () );

    gtk_window_set_position ( GTK_WINDOW ( file_selector ), GTK_WIN_POS_CENTER_ON_PARENT );


    preview = gtk_image_new ();
    gtk_file_chooser_set_preview_widget ( GTK_FILE_CHOOSER ( file_selector ), preview );
    g_signal_connect (G_OBJECT (file_selector),
                        "update-preview",
                        G_CALLBACK ( preferences_view_update_preview_logo ),
                        preview );

    switch ( gtk_dialog_run ( GTK_DIALOG ( file_selector ) ) )
    {
	case GTK_RESPONSE_OK:
	    change_logo_accueil ( file_selector );
	    gsb_file_update_last_path ( file_selection_get_last_directory (
                        GTK_FILE_CHOOSER ( file_selector ), TRUE ) );

	default:
	    gtk_widget_destroy ( file_selector );
	    break;
    }

    return ( FALSE );
}

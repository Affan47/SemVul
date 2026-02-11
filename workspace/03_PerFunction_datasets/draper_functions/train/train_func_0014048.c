run_filter( ScintillaObject *sci )
{
    int r , ret = 0 ;
    gchar *result = NULL ;

    gms_command = gms_get_str_command(gms_hnd);
    r = system( gms_command ) ;
    if ( r != 0 )
    {
        GtkWidget *dlg ;
        result = read_result_file( gms_get_error_filename(gms_hnd) ) ;

        dlg = gtk_message_dialog_new( GTK_WINDOW(geany->main_widgets->window),
                        GTK_DIALOG_DESTROY_WITH_PARENT,
                        GTK_MESSAGE_ERROR,
                        GTK_BUTTONS_CLOSE,
                        "%s", result);

        gtk_dialog_run(GTK_DIALOG(dlg));
        gtk_widget_destroy(GTK_WIDGET(dlg)) ;
		ret = -1 ;
    }
    else
    {
        result = read_result_file( gms_get_out_filename(gms_hnd) ) ;

        if ( gms_get_output_mode( gms_hnd) == OUT_CURRENT_DOC )
        {
            if ( gms_get_input_mode( gms_hnd) != IN_SELECTION )
                select_entirely_doc(  sci  ) ;

            update_doc( sci, result ) ;
        }
        else
        {
            document_new_file( NULL, NULL, result ) ;
        }
    }
    GMS_G_FREE( result ) ;

	return ret ;
}

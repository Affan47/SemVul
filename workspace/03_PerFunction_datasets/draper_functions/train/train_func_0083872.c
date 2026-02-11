saisie_echeance_accueil ( GtkWidget *event_box,
                        GdkEventButton *event,
                        gint scheduled_number )
{
    GtkWidget *parent_save, *dialog, *hbox;
    GtkWidget *button;
    gint result;

    parent_save = form_transaction_part -> parent;


    dialog = gtk_dialog_new_with_buttons ( _("Enter a scheduled transaction"),
					   GTK_WINDOW ( window ),
					   GTK_DIALOG_MODAL,
					   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					   GTK_STOCK_OK, GTK_RESPONSE_OK,
					   NULL );

    gtk_window_set_position ( GTK_WINDOW ( dialog ), GTK_WIN_POS_CENTER_ON_PARENT );
    gtk_widget_set_size_request ( dialog, 700, -1 );
    gtk_window_set_resizable ( GTK_WINDOW ( dialog ), TRUE );
    gtk_dialog_set_default_response ( GTK_DIALOG (dialog), GTK_RESPONSE_OK );


	hbox = gtk_hbox_new ( FALSE, 0 );
	gtk_box_pack_start ( GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox, TRUE, TRUE, 0 );
	gtk_container_set_border_width ( GTK_CONTAINER(hbox), 12 );
	gtk_widget_reparent ( form_transaction_part, hbox );
    gtk_widget_show_all ( hbox );


    button = gsb_form_scheduler_get_element_widget( SCHEDULED_FORM_ACCOUNT );
    g_signal_handlers_block_by_func ( G_OBJECT ( button ),
                        G_CALLBACK (gsb_form_scheduler_change_account),
                        NULL );

    gsb_form_fill_from_account (gsb_data_scheduled_get_account_number (scheduled_number));


    gsb_scheduler_list_execute_transaction(scheduled_number);

    g_signal_handlers_unblock_by_func ( G_OBJECT ( button ),
                        G_CALLBACK (gsb_form_scheduler_change_account),
                        NULL );

	result = gtk_dialog_run ( GTK_DIALOG ( dialog ));

    if ( result == GTK_RESPONSE_OK )
	 gsb_form_finish_edition ();

    gtk_widget_reparent ( form_transaction_part, parent_save );
    gtk_widget_destroy ( dialog );


    update_liste_echeances_manuelles_accueil (TRUE);
    update_liste_comptes_accueil (TRUE);
    return FALSE;
}

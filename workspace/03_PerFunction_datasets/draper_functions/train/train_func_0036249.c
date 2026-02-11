gsb_import_create_imported_transactions ( struct struct_compte_importation *imported_account,
                        gint account_number )
{
    GtkWidget *progress = NULL;
    GSList *list_tmp;
    gint nbre_transaction;

    mother_transaction_number = 0;

    list_tmp = imported_account -> operations_importees;
    nbre_transaction = g_slist_length ( list_tmp );

    if ( nbre_transaction > NBRE_TRANSACTION_FOR_PROGRESS_BAR )
        progress = gsb_import_progress_bar_affiche ( imported_account );

    while ( list_tmp )
    {
        struct struct_ope_importation *imported_transaction;
        gint transaction_number;

        if ( nbre_transaction > NBRE_TRANSACTION_FOR_PROGRESS_BAR )
        {
            gsb_import_progress_bar_pulse ( progress, nbre_transaction );
            while ( gtk_events_pending () ) gtk_main_iteration ( );
            nbre_transaction --;
        }

        imported_transaction = list_tmp -> data;


        if (imported_account -> bouton_devise)
            imported_transaction -> devise = gsb_currency_get_currency_from_combobox (
                        imported_account -> bouton_devise );
        else
            imported_transaction -> devise = gsb_data_currency_get_number_by_code_iso4217 (
                        imported_account -> devise );

        transaction_number = gsb_import_create_transaction ( imported_transaction,
                        account_number, imported_account -> origine );


        if ( imported_account -> invert_transaction_amount )
            gsb_data_transaction_set_amount ( transaction_number,
                        gsb_real_opposite (gsb_data_transaction_get_amount (
                        transaction_number ) ) );


        gsb_transactions_list_append_new_transaction ( transaction_number, FALSE );

        list_tmp = list_tmp -> next;
    }

    if ( progress )
        gtk_widget_destroy ( progress );


    gsb_payee_update_combofix ();
}

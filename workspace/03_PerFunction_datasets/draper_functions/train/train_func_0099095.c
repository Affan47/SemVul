gsb_form_transaction_currency_changed ( GtkWidget *widget, gpointer null )
{
    gint account_number;
    gint currency_number;
    gint account_currency_number;
    gint transaction_number;
    gint link_number;

    account_number = gsb_form_get_account_number ( );
    gtk_widget_grab_focus ( gsb_form_widget_get_widget ( TRANSACTION_FORM_DATE ) );

    account_currency_number = gsb_data_account_get_currency ( account_number );

    transaction_number = GPOINTER_TO_INT ( g_object_get_data (
                        G_OBJECT ( gsb_form_get_form_widget ( ) ),
                        "transaction_number_in_form" ) );

    currency_number = gsb_currency_get_currency_from_combobox ( widget );
    if ( account_currency_number == currency_number )
        gtk_widget_hide ( gsb_form_widget_get_widget ( TRANSACTION_FORM_CHANGE ) );
    else
        gtk_widget_show ( gsb_form_widget_get_widget ( TRANSACTION_FORM_CHANGE ) );

    link_number = gsb_data_currency_link_search ( account_currency_number,
                        currency_number );
    if ( link_number == 0 )
    {
        if ( gsb_data_transaction_get_marked_transaction ( transaction_number ) == OPERATION_RAPPROCHEE )
        {
            gtk_widget_set_sensitive ( widget, FALSE );
            gtk_widget_hide ( gsb_form_widget_get_widget (
                        TRANSACTION_FORM_CHANGE ) );
        }
        else if ( transaction_number == -1 )
            gsb_currency_exchange_dialog ( account_currency_number,
                        currency_number,
                        0,
                        null_real,
                        null_real,
                        TRUE );
        else
        {
            gsb_currency_exchange_dialog ( account_currency_number,
                        currency_number,
                        gsb_data_transaction_get_change_between ( transaction_number ),
                        gsb_data_transaction_get_exchange_rate ( transaction_number ),
                        gsb_data_transaction_get_exchange_fees ( transaction_number ),
                        TRUE );
        }
    }
    else if ( transaction_number > 0 )
    {
        gsb_currency_set_current_exchange ( gsb_data_transaction_get_exchange_rate ( transaction_number ) );
        gsb_currency_set_current_exchange_fees ( gsb_data_transaction_get_exchange_fees ( transaction_number ) );
    }
}

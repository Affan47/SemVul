gsb_navigation_update_statement_label ( gint account_number )
{
    gint reconcile_number;
    gchar* tmp_str;
    gchar* tmp_str1;
    gchar* tmp_str2;
    gsb_real amount;

    reconcile_number = gsb_data_reconcile_get_account_last_number ( account_number );
    amount = gsb_data_account_get_marked_balance ( account_number );
    if ( reconcile_number )
    {
        tmp_str1 = gsb_format_gdate ( gsb_data_reconcile_get_final_date (
                                            reconcile_number ) );
        tmp_str2 = gsb_real_get_string_with_currency ( amount,
                        gsb_data_account_get_currency ( account_number ), TRUE );

        tmp_str = g_strconcat ( _("Last statement: "), tmp_str1, " - ",
                               _("Reconciled balance: "), tmp_str2, NULL );
        gtk_label_set_text ( GTK_LABEL ( label_last_statement ), tmp_str);
        g_free ( tmp_str );
        g_free ( tmp_str1 );
        g_free ( tmp_str2 );
    }
    else if ( amount.mantissa != 0 )
    {
        tmp_str2 = gsb_real_get_string_with_currency (amount,
                        gsb_data_account_get_currency ( account_number ), TRUE );

        tmp_str = g_strconcat ( _("Last statement: none"), " - ",
                               _("Reconciled balance: "), tmp_str2, NULL );
        gtk_label_set_text ( GTK_LABEL ( label_last_statement ), tmp_str);
        g_free ( tmp_str );
        g_free ( tmp_str2 );
    }
    else
        gtk_label_set_text ( GTK_LABEL ( label_last_statement ),
                                            _("Last statement: none") );
}

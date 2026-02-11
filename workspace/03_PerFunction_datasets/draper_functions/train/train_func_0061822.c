bet_future_get_category_data ( GtkWidget *widget,
                        gint struct_type,
                        gpointer *value )
{
    const gchar *string;
    gchar **tab_char;
    gint category_number = 0;
    gint sub_category_number = 0;

    string = gtk_combofix_get_text ( GTK_COMBOFIX ( widget ) );

    if ( struct_type == 0 )
    {
        struct_futur_data *sd = ( struct_futur_data *) value;

        if ( string && strlen ( string ) > 0 )
        {
            tab_char = g_strsplit ( string, " : ", 2 );
            if ( my_strcasecmp ( tab_char[0], _("Transfer") ) == 0 )
            {
                sd -> is_transfert = TRUE;
                sd -> account_transfert =  gsb_data_account_get_no_account_by_name ( tab_char[1] );
            }
            else
            {
                category_number = gsb_data_category_get_number_by_name (
                                tab_char[0], FALSE, 0 );

                if ( tab_char[1] && strlen ( tab_char[1] ) )
                    sub_category_number = gsb_data_category_get_sub_category_number_by_name (
                                category_number, tab_char[1], FALSE );
                else
                    sub_category_number = 0;
            }

            g_strfreev ( tab_char );
        }
        else
        {
            category_number = 0;
            category_number = 0;
        }

        sd -> category_number = category_number;
        sd -> sub_category_number = sub_category_number;
    }
    else if ( struct_type == 1 )
    {
        struct_transfert_data *sd = ( struct_transfert_data *) value;

        if ( string && strlen ( string ) > 0 )
        {
            tab_char = g_strsplit ( string, " : ", 2 );
            category_number = gsb_data_category_get_number_by_name (
                            tab_char[0], FALSE, 0 );

            if ( tab_char[1] && strlen ( tab_char[1] ) )
                sub_category_number = gsb_data_category_get_sub_category_number_by_name (
                            category_number, tab_char[1], FALSE );
            else
                sub_category_number = 0;

            g_strfreev ( tab_char );
        }
        else
        {
            category_number = 0;
            category_number = 0;
        }

        sd -> category_number = category_number;
        sd -> sub_category_number = sub_category_number;
    }

    return FALSE;
}

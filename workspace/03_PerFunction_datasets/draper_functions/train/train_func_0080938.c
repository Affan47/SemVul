gsb_transfert_get_str_amount ( gsb_real amount,
                        gint account_currency,
                        gint replace_currency,
                        gint floating_point )
{
    gsb_real tmp_real = null_real;
    gint link_number;

    if ( ( link_number = gsb_data_currency_link_search ( account_currency, replace_currency ) ) )
    {
        if ( gsb_data_currency_link_get_first_currency ( link_number ) == replace_currency )
            tmp_real = gsb_real_mul ( amount,
                        gsb_data_currency_link_get_change_rate ( link_number ) );
        else
            tmp_real = gsb_real_div ( amount,
                        gsb_data_currency_link_get_change_rate ( link_number ) );
    }
    else if ( account_currency > 0 && replace_currency > 0 )
    {
        gchar *tmp_str;

        tmp_str = g_strdup ( _("Error: is missing one or more links between currencies.\n"
                        "You need to fix it and start over.") );
        dialogue_error ( tmp_str );

        g_free ( tmp_str );
    }

    return tmp_real;
}

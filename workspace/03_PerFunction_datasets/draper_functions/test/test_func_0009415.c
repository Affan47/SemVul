gsb_data_currency_link_set_modified_date ( gint currency_link_number,
                        GDate *date )
{
    struct_currency_link *currency_link;

    currency_link = gsb_data_currency_link_get_structure ( currency_link_number );

    if ( !currency_link )
        return FALSE;

    if ( !date )
        return FALSE;

    if ( currency_link -> modified_date )
        g_date_free ( currency_link -> modified_date );

    currency_link -> modified_date = gsb_date_copy ( date );

    return TRUE;
}

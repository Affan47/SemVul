gsb_data_currency_new ( const gchar *name )
{
    struct_currency *currency;

    currency = g_malloc0 ( sizeof ( struct_currency ));
    currency -> currency_number = gsb_data_currency_max_number () + 1;

    if (name)
	currency -> currency_name = my_strdup (name);
    else
	currency -> currency_name = NULL;

    currency_list = g_slist_append ( currency_list, currency );

    if ( ! gsb_data_currency_get_default_currency () )
	gsb_data_currency_set_default_currency ( currency -> currency_number );

    return currency -> currency_number;
}

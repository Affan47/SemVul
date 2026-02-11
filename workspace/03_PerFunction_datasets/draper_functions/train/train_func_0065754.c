gsb_currency_config_set_int_from_combobox ( GtkWidget *combobox, gint * dummy)
{
    gint *data;

    data = g_object_get_data ( G_OBJECT(combobox), "pointer" );

    if ( data )
    {
    *data = gsb_currency_get_currency_from_combobox (combobox);
    }


    if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );

    return (FALSE);
}

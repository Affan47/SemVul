initialise_largeur_colonnes_tab_affichage_ope ( gint type_operation, const gchar *description )
{
    gchar **pointeur_char;
    gint j;

    if ( description == NULL )
    {
        if ( type_operation == GSB_ACCOUNT_PAGE )
            description = transaction_col_width_init;
        else if ( type_operation == GSB_SCHEDULER_PAGE )
            description = scheduler_col_width_init;
    }


    pointeur_char = g_strsplit ( description, "-", 0 );

    if ( type_operation == GSB_ACCOUNT_PAGE )
    {
        for ( j = 0 ; j < CUSTOM_MODEL_VISIBLE_COLUMNS ; j++ )
            transaction_col_width[j] = utils_str_atoi ( pointeur_char[j] );
    }
    else if ( type_operation == GSB_SCHEDULER_PAGE )
    {
        for ( j = 0 ; j < SCHEDULER_COL_VISIBLE_COLUMNS ; j++ )
            scheduler_col_width[j] = utils_str_atoi ( pointeur_char[j] );
    }

        g_strfreev ( pointeur_char );
}

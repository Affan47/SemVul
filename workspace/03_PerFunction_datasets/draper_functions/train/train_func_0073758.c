bet_config_duration_number_changed ( GtkWidget *spin_button,
                        gpointer data )
{
    gint account_number;
    gint months;

    if ( GPOINTER_TO_INT ( data ) == 0 )
        account_number = bet_config_get_account_from_combo ( );
    else
        account_number = gsb_gui_navigation_get_current_account ( );

    months = gtk_spin_button_get_value_as_int ( GTK_SPIN_BUTTON ( spin_button ) );
    if ( gsb_data_account_get_bet_spin_range ( account_number ) == 1 )
        months *= 12;

    gsb_data_account_set_bet_months ( account_number, months );

    if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );

    gsb_data_account_set_bet_maj ( account_number, BET_MAJ_ESTIMATE );
    bet_data_update_bet_module ( account_number, -1 );

    return ( FALSE );
}

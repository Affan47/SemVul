gsb_transactions_list_display_show_gives_balance ( void )
{
    gint account_number;

    account_number = gsb_gui_navigation_get_current_account ( );
    devel_debug_int ( account_number);
    if ( account_number != -1 )
        gsb_transactions_list_update_tree_view ( account_number, TRUE );
}

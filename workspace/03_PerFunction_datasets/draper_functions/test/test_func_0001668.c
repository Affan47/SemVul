bet_data_select_bet_pages ( gint account_number )
{
    GtkWidget *page;
    kind_account kind;
    gint current_page;
    gint bet_use_budget;

    devel_debug_int ( account_number );

    kind = gsb_data_account_get_kind ( account_number );
    current_page = gtk_notebook_get_current_page ( GTK_NOTEBOOK ( account_page ) );
    bet_use_budget = gsb_data_account_get_bet_use_budget ( account_number );
    if ( bet_use_budget <= 0 )
        kind = GSB_TYPE_ASSET;
    else if ( etat.bet_deb_cash_account_option == 1 &&  kind == GSB_TYPE_CASH )
        kind = GSB_TYPE_BANK;

    switch ( kind )
    {
    case GSB_TYPE_BANK:
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_ESTIMATE_PAGE );
        gtk_widget_show ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_HISTORICAL_PAGE );
        gtk_widget_show ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_FINANCE_PAGE );
        gtk_widget_hide ( page );
        bet_historical_g_signal_unblock_tree_view ( );
        gsb_data_account_set_bet_maj ( account_number, BET_MAJ_ALL );
        if ( current_page < GSB_PROPERTIES_PAGE
         &&
         gsb_data_account_get_bet_use_budget ( account_number ) == FALSE )
            gtk_notebook_set_current_page ( GTK_NOTEBOOK ( account_page ), GSB_TRANSACTIONS_PAGE );
        if ( current_page == GSB_FINANCE_PAGE )
            gtk_notebook_set_current_page ( GTK_NOTEBOOK ( account_page ), GSB_ESTIMATE_PAGE );
        break;
    case GSB_TYPE_CASH:
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_ESTIMATE_PAGE );
        gtk_widget_hide ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_HISTORICAL_PAGE );
        gtk_widget_show ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_FINANCE_PAGE );
        gtk_widget_hide ( page );
        if ( current_page == GSB_ESTIMATE_PAGE || current_page == GSB_FINANCE_PAGE )
            gtk_notebook_set_current_page ( GTK_NOTEBOOK ( account_page ), GSB_HISTORICAL_PAGE );
        bet_historical_g_signal_block_tree_view ( );
        gsb_data_account_set_bet_maj ( account_number, BET_MAJ_HISTORICAL );
        break;
    case GSB_TYPE_LIABILITIES:
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_ESTIMATE_PAGE );
        gtk_widget_hide ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_HISTORICAL_PAGE );
        gtk_widget_hide ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_FINANCE_PAGE );
        gtk_widget_show ( page );
        if ( current_page == GSB_ESTIMATE_PAGE || current_page == GSB_HISTORICAL_PAGE )
            gtk_notebook_set_current_page ( GTK_NOTEBOOK ( account_page ), GSB_FINANCE_PAGE );
        break;
    case GSB_TYPE_ASSET:
        if ( current_page < GSB_PROPERTIES_PAGE )
            gtk_notebook_set_current_page ( GTK_NOTEBOOK ( account_page ), GSB_TRANSACTIONS_PAGE );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_ESTIMATE_PAGE );
        gtk_widget_hide ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_HISTORICAL_PAGE );
        gtk_widget_hide ( page );
        page = gtk_notebook_get_nth_page ( GTK_NOTEBOOK ( account_page ), GSB_FINANCE_PAGE );
        gtk_widget_hide ( page );
        break;
    }
}

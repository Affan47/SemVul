gsb_reconcile_update_amounts ( GtkWidget *entry,
					    gpointer null )
{
    gsb_real amount;
    gint account_number;
    gint currency_number;
    const gchar *initial_balance;
    const gchar *final_balance;
    gchar *tmp_string;
	gchar* tmpstr;
    gboolean valide = FALSE;


    account_number = gsb_gui_navigation_get_current_account ();


    initial_balance = gtk_entry_get_text ( GTK_ENTRY (reconcile_initial_balance_entry) );
    gtk_label_set_text ( GTK_LABEL ( reconcile_initial_balance_label ), initial_balance );

    if ( entry )
    {
        valide = gsb_form_widget_get_valide_amout_entry (
                        gtk_entry_get_text ( GTK_ENTRY ( entry ) ) );
        if ( valide )
        {

            gtk_widget_modify_base ( entry, GTK_STATE_NORMAL, NULL );
        }
        else
        {

            gtk_widget_modify_base ( entry, GTK_STATE_NORMAL,
                            &calendar_entry_color );
            return FALSE;
        }
    }

    currency_number = gsb_data_account_get_currency ( account_number );
    amount = gsb_utils_edit_calculate_entry ( reconcile_final_balance_entry );
    final_balance = gsb_real_get_string_with_currency ( amount, currency_number, FALSE );
    gtk_label_set_text ( GTK_LABEL ( reconcile_final_balance_label ), final_balance );


    tmp_string = gsb_real_get_string_with_currency (
                        gsb_data_account_calculate_waiting_marked_balance ( account_number ),
                        currency_number,
                        FALSE );
    gtk_label_set_text ( GTK_LABEL ( reconcile_marked_balance_label ), tmp_string );
    g_free (tmp_string);


    amount = gsb_real_sub ( gsb_real_add (
                        gsb_real_get_from_string ( initial_balance ),
					    gsb_data_account_calculate_waiting_marked_balance ( account_number ) ),
			            gsb_real_get_from_string ( final_balance ) );

    tmpstr = gsb_real_get_string_with_currency ( amount, currency_number, FALSE );
    gtk_label_set_text ( GTK_LABEL ( reconcile_variation_balance_label ), tmpstr);
    g_free ( tmpstr );

    if ( amount.mantissa )
	    gtk_widget_set_sensitive ( GTK_WIDGET ( reconcile_ok_button ), FALSE );
    else
	    gtk_widget_set_sensitive ( GTK_WIDGET ( reconcile_ok_button ), TRUE );
    return FALSE;
}

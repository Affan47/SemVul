gsb_payment_method_changed_callback ( GtkWidget *combo_box,
                        gpointer null )
{
    gint payment_number;
    GtkWidget *cheque_entry;

    cheque_entry = gsb_form_widget_get_widget (TRANSACTION_FORM_CHEQUE);
    if ( !cheque_entry )
        return FALSE;

    payment_number = gsb_payment_method_get_selected_number (combo_box);
    if ( !payment_number )
        return FALSE;

    devel_debug_int (payment_number);

    if ( gsb_data_payment_get_show_entry ( payment_number) )
    {

        if (gsb_data_payment_get_automatic_numbering ( payment_number ) )
        {
            if ( gsb_form_widget_check_empty (cheque_entry) )
            {
				gchar* tmp_str;
                gint transaction_number;
                gboolean is_transaction;

                transaction_number = GPOINTER_TO_INT ( g_object_get_data (
                                            G_OBJECT ( gsb_form_get_form_widget ( ) ),
							                "transaction_number_in_form" ) );
                if ( gsb_form_get_origin () == ORIGIN_VALUE_SCHEDULED )
                    is_transaction = FALSE;
                else
                    is_transaction = TRUE;
                if ( gsb_data_mix_get_mother_transaction_number ( transaction_number,
                 is_transaction ) == 0 )
                {
                    tmp_str = gsb_data_payment_incremente_last_number ( payment_number, 1 );
                }
                else
                    tmp_str = g_strdup ( gsb_data_payment_get_last_number ( payment_number ) );

                gsb_form_entry_get_focus (cheque_entry);
                gtk_entry_set_text ( GTK_ENTRY (cheque_entry), tmp_str);
                g_free ( tmp_str );
            }
        }
        else
            gsb_payment_method_set_cheque_entry ( 0 );

        gtk_widget_show (cheque_entry);
    }
    else
        gtk_widget_hide (cheque_entry);

    return FALSE;
}

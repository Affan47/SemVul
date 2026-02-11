gsb_form_fill_by_transaction ( gint transaction_number,
                        gint is_transaction,
                        gboolean grab_focus )
{
    gint mother_number;
    gint account_number;
    gint focus_to;
    gint is_split;
    GSList *tmp_list;

    devel_debug_int (transaction_number);

    if ( !transaction_number )
        return FALSE;


    account_number = gsb_data_mix_get_account_number (transaction_number, is_transaction);
    mother_number = gsb_data_mix_get_mother_transaction_number (transaction_number, is_transaction);
    is_split = gsb_data_mix_get_split_of_transaction (transaction_number, is_transaction);


    if (account_number == -1)
        account_number = gsb_form_get_account_number ();


    gsb_form_show ( TRUE );

    if ( !is_transaction )
    {


    gsb_form_scheduler_set ( transaction_number );
    }


    if ( transaction_number == -1 )
    {
        GtkWidget *date_entry;


        if ( !grab_focus )
            return FALSE;

        date_entry = gsb_form_widget_get_widget (TRANSACTION_FORM_DATE);

        if ( gsb_form_widget_check_empty (date_entry))


            gsb_form_button_press_event ( date_entry,
                          NULL,
                          GINT_TO_POINTER (TRANSACTION_FORM_DATE));

        gtk_editable_select_region ( GTK_EDITABLE (date_entry), 0, -1);
        gtk_widget_grab_focus ( GTK_WIDGET (date_entry));

        return FALSE;
    }


    g_object_set_data ( G_OBJECT ( transaction_form ),
			"transaction_number_in_form",
			GINT_TO_POINTER (transaction_number));

    gsb_form_change_sensitive_buttons (TRUE);


    gsb_form_set_sensitive (is_split, mother_number);


    tmp_list = gsb_form_widget_get_list ();

    while (tmp_list)
    {
        struct_element *element;

        element = tmp_list -> data;

        if (mother_number
            &&
            transaction_number < 0)
        {


            switch (element -> element_number)
            {
            case TRANSACTION_FORM_DATE:
            case TRANSACTION_FORM_VALUE_DATE:
            case TRANSACTION_FORM_PARTY:
            case TRANSACTION_FORM_TYPE:
            case TRANSACTION_FORM_CHEQUE:
            case TRANSACTION_FORM_DEVISE:
            case TRANSACTION_FORM_BANK:
                gsb_form_fill_element ( element -> element_number,
                            account_number,
                            mother_number,
                            is_transaction );
                break;
            }
        }
        else

            gsb_form_fill_element ( element -> element_number,
                        account_number,
                        transaction_number,
                        is_transaction );

        tmp_list = tmp_list -> next;
    }


    if (is_transaction)
    {
        gint contra_transaction_number;


        contra_transaction_number = gsb_data_transaction_get_contra_transaction_number ( transaction_number );


        if ( gsb_data_transaction_get_marked_transaction (transaction_number) == OPERATION_RAPPROCHEE
         && mother_number == 0 )
        {
            gtk_widget_set_sensitive ( gsb_form_widget_get_widget (TRANSACTION_FORM_DEBIT), FALSE );
            gtk_widget_set_sensitive ( gsb_form_widget_get_widget (TRANSACTION_FORM_CREDIT), FALSE );
        }


        if ( contra_transaction_number > 0
         &&
         gsb_data_transaction_get_marked_transaction (contra_transaction_number) == OPERATION_RAPPROCHEE )
        {
            gtk_widget_set_sensitive ( gsb_form_widget_get_widget (TRANSACTION_FORM_DEBIT), FALSE );
            gtk_widget_set_sensitive ( gsb_form_widget_get_widget (TRANSACTION_FORM_CREDIT), FALSE );


            gtk_widget_set_sensitive ( gsb_form_widget_get_widget (TRANSACTION_FORM_CATEGORY), FALSE );
        }
    }


    if (grab_focus)
    {
        GtkWidget *widget;


        if (mother_number)
            focus_to = gsb_form_widget_next_element ( account_number,
						      TRANSACTION_FORM_DATE,
						      GSB_RIGHT );
        else
            focus_to = TRANSACTION_FORM_DATE;

        widget = gsb_form_widget_get_widget ( focus_to );
        gtk_editable_select_region ( GTK_EDITABLE ( widget ), 0, -1 );
        if ( !is_transaction && gtk_widget_is_focus ( widget ) )
            gsb_form_widget_entry_get_focus ( widget, NULL, GINT_TO_POINTER ( focus_to ) );
        else
            gtk_widget_grab_focus ( widget );

    }

    return FALSE;
}

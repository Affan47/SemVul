gsb_payment_method_config_name_changed ( GtkWidget *entry,
						  GtkWidget *tree_view )
{
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    gboolean good;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view));
    good = gtk_tree_selection_get_selected (selection, NULL, &iter);

    if (good)
    {
	GtkTreeModel *model;
	gint payment_number;

	model = gtk_tree_view_get_model ( GTK_TREE_VIEW (tree_view));
	gtk_tree_model_get ( GTK_TREE_MODEL(model), &iter,
			     PAYMENT_METHODS_NUMBER_COLUMN, &payment_number,
			     -1 );

	if (payment_number)
	{

	    gtk_tree_store_set (GTK_TREE_STORE (model), &iter,
				PAYMENT_METHODS_NAME_COLUMN, gsb_data_payment_get_name (payment_number),
				-1);
	    gsb_reconcile_sort_config_fill ();


	    if ( gsb_data_form_check_for_value ( TRANSACTION_FORM_TYPE ))
	    {
		GtkWidget *widget;
		gint account_number;

		account_number = gsb_form_get_account_number ();
		widget = gsb_form_widget_get_widget (TRANSACTION_FORM_TYPE);

		if (widget)
		{
		    gsb_payment_method_create_combo_list ( widget,
							   GSB_PAYMENT_DEBIT,
							   account_number, 0, FALSE );

		    if (GTK_WIDGET_VISIBLE (widget))
		    {
			gsb_payment_method_set_combobox_history ( widget,
								  gsb_data_account_get_default_debit (account_number), TRUE );
		    }
		    else
		    {
			gtk_widget_hide ( gsb_form_widget_get_widget (TRANSACTION_FORM_CHEQUE));
		    }
		}
	    }

	    transaction_list_update_element (ELEMENT_PAYMENT_TYPE);
	}
    }
    return FALSE;
}

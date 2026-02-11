gsb_payment_method_config_remove ( GtkWidget *button,
					    GtkWidget *tree_view )
{
    gint payment_number;
    gint account_number;
    GtkTreeSelection * selection;
    GtkTreeIter iter;
    gboolean good;
    GSList *list_tmp_transactions;
    GtkTreeModel *model;


    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view));
    good = gtk_tree_selection_get_selected (selection, NULL, &iter);

    if ( !good )
	return FALSE;

    model = gtk_tree_view_get_model (GTK_TREE_VIEW (tree_view));
    gtk_tree_model_get ( GTK_TREE_MODEL(model), &iter,
			 PAYMENT_METHODS_NUMBER_COLUMN, &payment_number,
			 -1 );
    if ( !payment_number )
	return FALSE;


    list_tmp_transactions = gsb_data_transaction_get_complete_transactions_list ();
    while (list_tmp_transactions)
    {
	gint transaction_number;
	transaction_number = gsb_data_transaction_get_transaction_number (list_tmp_transactions -> data);

	if ( gsb_data_transaction_get_method_of_payment_number (transaction_number) == payment_number)
	{

	    if ( !gsb_payment_method_config_switch_payment (payment_number))
		return FALSE;
	    list_tmp_transactions = NULL;
	}
	else
	    list_tmp_transactions = list_tmp_transactions -> next;
    }

    account_number = gsb_data_payment_get_account_number (payment_number);


    switch (gsb_data_payment_get_sign (payment_number))
    {
	case GSB_PAYMENT_DEBIT:
	    if ( gsb_data_account_get_default_debit (account_number) == payment_number)
	    {
		gsb_data_account_set_default_debit ( account_number,
						     gsb_payment_method_config_get_transaction_by_sign (account_number,
										  GSB_PAYMENT_DEBIT,
										  payment_number));
	    }
	    break;

	case GSB_PAYMENT_CREDIT:
	    if ( gsb_data_account_get_default_credit (account_number) == payment_number)
	    {
		gsb_data_account_set_default_credit ( account_number,
						      gsb_payment_method_config_get_transaction_by_sign (account_number,
										   GSB_PAYMENT_CREDIT,
										   payment_number));
	    }
	    break;
    }


    gsb_data_account_sort_list_remove ( account_number,
					payment_number );


    gtk_tree_store_remove ( GTK_TREE_STORE(model), &iter );
    gsb_data_payment_remove (payment_number);

    if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );
    return FALSE;
}

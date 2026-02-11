gsb_payment_method_config_fill_list ( GtkTreeModel *model)
{
    GSList *list_tmp;

    gtk_tree_store_clear ( GTK_TREE_STORE (model) );


    list_tmp = gsb_data_account_get_list_accounts ();

    while ( list_tmp )
    {
	gint account_number;
	GSList *payment_list;
	GtkTreeIter account_iter, debit_iter, credit_iter;

	account_number = gsb_data_account_get_no_account ( list_tmp -> data );

	gtk_tree_store_append (GTK_TREE_STORE (model), &account_iter, NULL);
	gtk_tree_store_set (GTK_TREE_STORE (model), &account_iter,
			    PAYMENT_METHODS_NAME_COLUMN, gsb_data_account_get_name (account_number),
			    PAYMENT_METHODS_NUMBERING_COLUMN, NULL,
			    PAYMENT_METHODS_TYPE_COLUMN, 0,
			    PAYMENT_METHODS_DEFAULT_COLUMN, FALSE,
			    PAYMENT_METHODS_ACTIVABLE_COLUMN, FALSE,
			    PAYMENT_METHODS_VISIBLE_COLUMN, FALSE,
			    PAYMENT_METHODS_NUMBER_COLUMN, NULL,
			    PAYMENT_METHODS_ACCOUNT_COLUMN, account_number,
			    -1 );


	gtk_tree_store_append (GTK_TREE_STORE (model), &debit_iter, &account_iter);
	gtk_tree_store_set (GTK_TREE_STORE (model), &debit_iter,
			    PAYMENT_METHODS_NAME_COLUMN, _("Debit"),
			    PAYMENT_METHODS_NUMBERING_COLUMN, NULL,
			    PAYMENT_METHODS_TYPE_COLUMN, 0,
			    PAYMENT_METHODS_DEFAULT_COLUMN, FALSE,
			    PAYMENT_METHODS_ACTIVABLE_COLUMN, FALSE,
			    PAYMENT_METHODS_VISIBLE_COLUMN, FALSE,
			    PAYMENT_METHODS_NUMBER_COLUMN, NULL,
			    PAYMENT_METHODS_ACCOUNT_COLUMN, account_number,
			    -1 );


	gtk_tree_store_append (GTK_TREE_STORE (model), &credit_iter, &account_iter);
	gtk_tree_store_set (GTK_TREE_STORE (model), &credit_iter,
			    PAYMENT_METHODS_NAME_COLUMN, _("Credit"),
			    PAYMENT_METHODS_NUMBERING_COLUMN, NULL,


			    PAYMENT_METHODS_TYPE_COLUMN, 0,
			    PAYMENT_METHODS_DEFAULT_COLUMN, FALSE,
			    PAYMENT_METHODS_ACTIVABLE_COLUMN, FALSE,
			    PAYMENT_METHODS_VISIBLE_COLUMN, FALSE,
			    PAYMENT_METHODS_NUMBER_COLUMN, NULL,
			    PAYMENT_METHODS_ACCOUNT_COLUMN, account_number,
			    -1 );


	payment_list = gsb_data_payment_get_payments_list ();
	while (payment_list)
	{
	    gint payment_number;
	    GtkTreeIter *parent_iter = NULL;
	    GtkTreeIter method_iter;
	    gboolean isdefault;
	    const gchar *number;

	    payment_number = gsb_data_payment_get_number (payment_list -> data);


	    if (gsb_data_payment_get_account_number (payment_number) != account_number)
	    {
		payment_list = payment_list -> next;
		continue;
	    }


	    if ( payment_number == gsb_data_account_get_default_debit (account_number)
		 ||
		 payment_number == gsb_data_account_get_default_credit (account_number) )
		isdefault = 1;
	    else
		isdefault = 0;


	    switch (gsb_data_payment_get_sign (payment_number))
	    {
		case GSB_PAYMENT_NEUTRAL:
		    parent_iter = &account_iter;
		    break;
		case GSB_PAYMENT_DEBIT:
		    parent_iter = &debit_iter;
		    break;
		case GSB_PAYMENT_CREDIT:
		    parent_iter = &credit_iter;
		    break;
	    }


	    if ( gsb_data_payment_get_automatic_numbering (payment_number))
		number = gsb_data_payment_get_last_number ( payment_number );
	    else
		number = g_strdup("");


	    gtk_tree_store_append (GTK_TREE_STORE (model), &method_iter, parent_iter);
	    gtk_tree_store_set (GTK_TREE_STORE (model), &method_iter,
				PAYMENT_METHODS_NAME_COLUMN, gsb_data_payment_get_name (payment_number),
				PAYMENT_METHODS_NUMBERING_COLUMN, number,
				PAYMENT_METHODS_TYPE_COLUMN, gsb_data_payment_get_sign (payment_number),
				PAYMENT_METHODS_DEFAULT_COLUMN, isdefault,
				PAYMENT_METHODS_ACTIVABLE_COLUMN, gsb_data_payment_get_sign (payment_number) != 0,
				PAYMENT_METHODS_VISIBLE_COLUMN, gsb_data_payment_get_sign (payment_number) != 0,
				PAYMENT_METHODS_NUMBER_COLUMN, payment_number,
				PAYMENT_METHODS_ACCOUNT_COLUMN, account_number,
				-1 );

	    payment_list = payment_list -> next;
	}
	list_tmp = list_tmp -> next;
    }
}

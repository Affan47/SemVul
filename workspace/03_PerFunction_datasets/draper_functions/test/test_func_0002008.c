gsb_account_set_combo_account_number ( GtkWidget *combo_box,
						gint account_number )

{
    GtkTreeIter iter;
    GtkTreeModel *model;

    if (!combo_box
	||
	!GTK_IS_COMBO_BOX (combo_box))
	return FALSE;

    model = gtk_combo_box_get_model (GTK_COMBO_BOX (combo_box));

    if (!gtk_tree_model_get_iter_first (model, &iter))
	return FALSE;

    do
    {
	gint account_test;

	gtk_tree_model_get ( model,
			     &iter,
			     1, &account_test,
			     -1 );
	if (account_number == account_test)
	{
	    gtk_combo_box_set_active_iter ( GTK_COMBO_BOX (combo_box),
					    &iter );
	    return TRUE;
	}
    }
    while (gtk_tree_model_iter_next (model, &iter));

    return FALSE;
}

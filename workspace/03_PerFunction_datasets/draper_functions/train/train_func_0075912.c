gsb_combo_box_set_index ( GtkWidget *combo_box,
			       gint index )
{
    GtkTreeIter iter;
    GtkTreeModel *model;


    if (!combo_box)
	return FALSE;

    model = gtk_combo_box_get_model ( GTK_COMBO_BOX (combo_box));

    if ( gtk_tree_model_get_iter_first (model, &iter))
    {
	do
	{
	    gint number;

	    gtk_tree_model_get ( model, &iter,
				 1, &number,
				 -1 );
	    if (number == index)
	    {
		gtk_combo_box_set_active_iter ( GTK_COMBO_BOX (combo_box),
						&iter );
		return TRUE;
	    }
	}
	while (gtk_tree_model_iter_next (model, &iter));
    }
    return FALSE;
}

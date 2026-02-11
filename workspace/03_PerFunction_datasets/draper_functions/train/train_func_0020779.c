gsb_currency_config_get_selected ( GtkTreeView *tree_view )
{
    GtkTreeSelection * selection = gtk_tree_view_get_selection ( tree_view );
    GtkTreeIter iter;
    GtkTreeModel * tree_model;
    gint currency_number;

    if ( !selection || ! gtk_tree_selection_get_selected (selection, &tree_model, &iter))
	return(FALSE);

    gtk_tree_model_get ( tree_model,
			 &iter,
			 CURRENCY_NUMBER_COLUMN, &currency_number,
			 -1 );
    return currency_number;
}

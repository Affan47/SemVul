report_tree_view_selection_changed ( GtkTreeSelection *selection,
					      GtkTreeModel *model )
{
    GtkTreeIter iter;
    gint selected;

    if (! gtk_tree_selection_get_selected (selection, NULL, &iter))
	return(FALSE);

    gtk_tree_model_get ( model, &iter, 1, &selected, -1 );
    gtk_notebook_set_current_page ( GTK_NOTEBOOK ( notebook_config_etat ), selected);

    return FALSE;
}

ui_acc_listview_get_selected_key(GtkTreeView *treeview)
{
GtkTreeSelection *selection;
GtkTreeModel		 *model;
GtkTreeIter			 iter;

	selection = gtk_tree_view_get_selection(treeview);
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
	Account *item;

		gtk_tree_model_get(model, &iter, LST_DEFACC_DATAS, &item, -1);

		if( item!= NULL	 )
			return item->key;
	}
	return 0;
}

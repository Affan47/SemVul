cb_delete()
{
	int	row = getselectedhost();
	int	n;
	GtkTreeIter  iter;

	if  (row < 0)
		return;
	hostnum--;
	for  (n = row;  n < hostnum;  n++)
		hostlist[n] = hostlist[n+1];
	if  (gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(hlist_store), &iter, NULL, row))
		gtk_list_store_remove(GTK_LIST_STORE(hlist_store), &iter);
}

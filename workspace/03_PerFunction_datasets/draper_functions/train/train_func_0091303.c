remove_children(GtkTreeModel *model, GtkTreeIter *parent)
{
	GtkTreeIter child;
	if (gtk_tree_model_iter_children(model, &child, parent))
	{
		while(gtk_tree_store_remove(GTK_TREE_STORE(model), &child))
			;
	}
}

remove_old(GtkTreeModel *model, int updated)
{
	GtkTreePath *path = gtk_tree_path_new_first();
	GtkTreeIter iter;
	int i;


	if (gtk_tree_model_get_iter(model, &iter, path)) {
		while (1) {
			gtk_tree_model_get(model, &iter, updated, &i, -1);
			if (!i) {
				if (!gtk_tree_store_remove(
					    GTK_TREE_STORE(model),
					    &iter))
					break;
				else
					continue;
			}
			if (!gtk_tree_model_iter_next(model, &iter)) {
				break;
			}
		}
	}
	gtk_tree_path_free(path);
}

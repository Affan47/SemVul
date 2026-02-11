cb_dialog_function_load_recent_funcs(GtkTreeModel *model,
				     G_GNUC_UNUSED GtkTreePath *path,
				     GtkTreeIter *iter,
				     gpointer data)
{
	gpointer this;

	gtk_tree_model_get (model, iter,
			    FUNCTION, &this,
			    -1);
	if (this == data) {
		gtk_list_store_set (GTK_LIST_STORE (model), iter,
				    FUNCTION_RECENT, TRUE,
				    -1);
		return TRUE;
	}
	return FALSE;
}

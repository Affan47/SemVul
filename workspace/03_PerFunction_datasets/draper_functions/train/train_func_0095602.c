on_global_vars_text_changed (GtkCellRendererText *cell,
                             gchar *path_string,
                             gchar *new_text,
                             gpointer user_data)
{
	GtkTreeModel *global_vars_model = NULL;
	SnippetsDB *snippets_db = NULL;
	GtkTreePath *path = NULL;
	GtkTreeIter iter;
	gchar *name = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPETS_DB (user_data));
	snippets_db = ANJUTA_SNIPPETS_DB (user_data);
	global_vars_model = snippets_db_get_global_vars_model (snippets_db);
	g_return_if_fail (GTK_IS_TREE_MODEL (global_vars_model));


	path = gtk_tree_path_new_from_string (path_string);
	gtk_tree_model_get_iter (global_vars_model, &iter, path);


	gtk_tree_model_get (global_vars_model, &iter,
	                    GLOBAL_VARS_MODEL_COL_NAME, &name,
	                    -1);
	snippets_db_set_global_variable_value (snippets_db,
	                                       name,
	                                       new_text);
	g_free (name);


	snippets_db_save_global_vars (snippets_db);
}

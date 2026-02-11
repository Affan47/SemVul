dialog_formula_guru_load_fd (GtkTreePath *path, GnmFunc *fd,
			     FormulaGuruState *state)
{
	GtkTreeIter iter;
	gint min_arg, max_arg;
	GtkTreePath *new_path;

	gnm_func_load_if_stub (fd);

	if (path == NULL) {
		gtk_tree_store_clear (state->model);
		gtk_tree_store_append (state->model, &iter, NULL);
	} else if (!gtk_tree_model_get_iter (GTK_TREE_MODEL (state->model), &iter, path)) {
		GtkTreePath *new_path = gtk_tree_path_copy (path);
		if (gtk_tree_path_prev (new_path) &&
		    gtk_tree_model_get_iter (GTK_TREE_MODEL (state->model),
				      &iter, new_path)) {
			dialog_formula_guru_adjust_varargs (&iter, state);
			if (!gtk_tree_model_get_iter (GTK_TREE_MODEL (state->model),
						      &iter, path)) {
				gtk_tree_store_clear (state->model);
				gtk_tree_path_free (new_path);
				return 0;
			}
		} else {
			gtk_tree_store_clear (state->model);
			gtk_tree_path_free (new_path);
			return 0;
		}
		gtk_tree_path_free (new_path);
	}

	function_def_count_args (fd, &min_arg, &max_arg);

	gtk_tree_store_set (state->model, &iter,
			    FUN_ARG_ENTRY, "",
			    IS_NON_FUN, FALSE,
			    FUNCTION, fd,
			    MIN_ARG, min_arg,
			    MAX_ARG, max_arg,
			    -1);
	dialog_formula_guru_adjust_children (&iter, fd, state);
	dialog_formula_guru_adjust_varargs (&iter, state);

	new_path = gtk_tree_model_get_path (GTK_TREE_MODEL (state->model),
                                             &iter);
	gtk_tree_view_expand_row (state->treeview, new_path, FALSE);
	gtk_tree_path_free (new_path);

	return max_arg;
}

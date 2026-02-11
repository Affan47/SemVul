cb_destroyed_interpreter (GnmPyInterpreterSelector *sel,
                          GnmPyInterpreter *ex_interpreter)
{
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_combo_box_get_model (GTK_COMBO_BOX (sel));
	GtkTreePath *path = find_item_with_interpreter (sel, ex_interpreter);
	g_return_if_fail (path != NULL);

	GO_SLIST_REMOVE (sel->added_interpreters, ex_interpreter);
	if (gtk_tree_model_get_iter (model, &iter, path))
		gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
	else
		g_warning ("Did not get a valid iterator");
	gtk_tree_path_free (path);
	if (sel->cur_interpreter == ex_interpreter) {
		sel->cur_interpreter = gnm_python_get_default_interpreter (sel->py_object);
		path = find_item_with_interpreter (sel, sel->cur_interpreter);
		if (path) {
			gtk_combo_box_set_active (GTK_COMBO_BOX (sel), *gtk_tree_path_get_indices (path));
			gtk_tree_path_free (path);
		}
		g_signal_emit (sel, signals[INTERPRETER_CHANGED_SIGNAL], 0);
	}
}

go_action_combo_stack_truncate (GOActionComboStack *act, unsigned n)
{
	GOActionComboStack *saction = GO_ACTION_COMBO_STACK (act);
	GtkTreeIter iter;
	unsigned old_count;

	g_return_if_fail (saction != NULL);

	old_count = gtk_tree_model_iter_n_children (saction->model, NULL);

	if (gtk_tree_model_iter_nth_child (saction->model, &iter, NULL, n))
		while (gtk_list_store_remove (GTK_LIST_STORE (saction->model), &iter))
			;
	check_sensitivity (saction, old_count);
}

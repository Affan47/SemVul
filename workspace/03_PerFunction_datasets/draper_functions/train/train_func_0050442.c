sort_iter_to_contact_store_iter (ENameSelectorDialog *name_selector_dialog,
                                 GtkTreeIter *iter,
                                 gint *email_n)
{
	ETreeModelGenerator *contact_filter;
	GtkTreeIter          child_iter;
	gint                 email_n_local;

	contact_filter = e_name_selector_model_peek_contact_filter (
		name_selector_dialog->priv->name_selector_model);

	gtk_tree_model_sort_convert_iter_to_child_iter (
		name_selector_dialog->priv->contact_sort, &child_iter, iter);
	e_tree_model_generator_convert_iter_to_child_iter (
		contact_filter, iter, &email_n_local, &child_iter);

	if (email_n)
		*email_n = email_n_local;
}

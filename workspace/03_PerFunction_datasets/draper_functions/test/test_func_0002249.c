e_contact_store_iter_nth_child (GtkTreeModel *tree_model,
                                GtkTreeIter *iter,
                                GtkTreeIter *parent,
                                gint n)
{
	EContactStore *contact_store = E_CONTACT_STORE (tree_model);

	g_return_val_if_fail (E_IS_CONTACT_STORE (tree_model), FALSE);

	if (parent)
		return FALSE;

	if (n < count_contacts (contact_store)) {
		ITER_SET (contact_store, iter, n);
		return TRUE;
	}

	return FALSE;
}

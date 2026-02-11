e_categories_selector_set_checked (ECategoriesSelector *selector,
                                   const gchar *categories)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar **arr;
	gint i;

	g_return_if_fail (E_IS_CATEGORIES_SELECTOR (selector));


	g_hash_table_remove_all (selector->priv->selected_categories);

	arr = g_strsplit (categories, ",", 0);
	if (arr) {
		for (i = 0; arr[i] != NULL; i++) {
			g_strstrip (arr[i]);
			g_hash_table_insert (
				selector->priv->selected_categories,
				g_strdup (arr[i]), g_strdup (arr[i]));
		}
		g_strfreev (arr);
	}

	model = gtk_tree_view_get_model (GTK_TREE_VIEW (selector));
	if (gtk_tree_model_get_iter_first (model, &iter)) {
		do {
			gchar *category_name;
			gboolean found;

			gtk_tree_model_get (
				model, &iter,
				COLUMN_CATEGORY, &category_name,
				-1);
			found = (g_hash_table_lookup (
				selector->priv->selected_categories,
				category_name) != NULL);
			gtk_list_store_set (
				GTK_LIST_STORE (model), &iter,
				COLUMN_ACTIVE, found, -1);

			g_free (category_name);
		} while (gtk_tree_model_iter_next (model, &iter));
	}
}

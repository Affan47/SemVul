e_categories_selector_get_checked (ECategoriesSelector *selector)
{
	GString *str;
	GList *list, *category;

	g_return_val_if_fail (E_IS_CATEGORIES_SELECTOR (selector), NULL);

	str = g_string_new ("");
	list = g_hash_table_get_values (selector->priv->selected_categories);


	list = g_list_sort (list, (GCompareFunc) g_utf8_collate);

	for (category = list; category != NULL; category = category->next) {
		if (str->len > 0)
			g_string_append_printf (
				str, ",%s", (gchar *) category->data);
		else
			g_string_append (str, (gchar *) category->data);
	}

	g_list_free (list);

	return g_string_free (str, FALSE);
}

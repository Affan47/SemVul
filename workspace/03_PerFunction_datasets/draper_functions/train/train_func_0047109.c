tree_sort_func(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b,
		gpointer user_data)
{
	gboolean sort_by_name = GPOINTER_TO_INT(user_data);
	TMTag *tag_a, *tag_b;
	gint cmp;

	gtk_tree_model_get(model, a, SYMBOLS_COLUMN_TAG, &tag_a, -1);
	gtk_tree_model_get(model, b, SYMBOLS_COLUMN_TAG, &tag_b, -1);


	if (tag_a && !tag_has_missing_parent(tag_a, GTK_TREE_STORE(model), a) &&
		tag_b && !tag_has_missing_parent(tag_b, GTK_TREE_STORE(model), b))
	{
		cmp = sort_by_name ? compare_symbol(tag_a, tag_b) :
			compare_symbol_lines(tag_a, tag_b);
	}
	else
	{
		gchar *astr, *bstr;

		gtk_tree_model_get(model, a, SYMBOLS_COLUMN_NAME, &astr, -1);
		gtk_tree_model_get(model, b, SYMBOLS_COLUMN_NAME, &bstr, -1);


		if (gtk_tree_store_iter_depth(GTK_TREE_STORE(model), a) == 0)
		{
			cmp = compare_top_level_names(astr, bstr);
		}
		else
		{

			if (! astr)
				cmp = -(astr != bstr);
			else if (! bstr)
				cmp = astr != bstr;
			else
			{
				cmp = strcmp(astr, bstr);


				if (tag_a && tag_b)
					if (!sort_by_name ||
						(utils_str_equal(tag_a->name, tag_b->name) &&
							utils_str_equal(tag_a->atts.entry.scope, tag_b->atts.entry.scope)))
						cmp = compare_symbol_lines(tag_a, tag_b);
			}
		}
		g_free(astr);
		g_free(bstr);
	}
	tm_tag_unref(tag_a);
	tm_tag_unref(tag_b);

	return cmp;
}

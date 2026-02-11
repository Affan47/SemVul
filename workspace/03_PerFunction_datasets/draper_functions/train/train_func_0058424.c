get_all_themes (DialogData *data)
{
	GList        *list = NULL;
	GtkTreeModel *model;
	GtkTreeIter   iter;

	model = GTK_TREE_MODEL (GET_WIDGET ("theme_liststore"));
	if (gtk_tree_model_get_iter_first (model, &iter))
		do {
			GthContactSheetTheme *theme;

			gtk_tree_model_get (model, &iter,
					    THEME_COLUMN_THEME, &theme,
					    -1);
			if (theme != NULL)
				list = g_list_prepend (list, gth_contact_sheet_theme_ref (theme));
		}
		while (gtk_tree_model_iter_next (model, &iter));

	return g_list_reverse (list);
}

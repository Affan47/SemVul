on_inspect_hbit_update(const MenuItem *menu_item)
{
	GtkTreeIter iter;
	char *expr, *name;
	gint hb_mode = GPOINTER_TO_INT(menu_item->gdata);

	gtk_tree_selection_get_selected(selection, NULL, &iter);
	gtk_tree_model_get(model, &iter, INSPECT_EXPR, &expr, INSPECT_NAME, &name, -1);
	inspect_hbit_update_iter(&iter, hb_mode);
	parse_mode_update(expr, MODE_HBIT, hb_mode);

	if (name)
	{
		char *reverse = parse_mode_reentry(expr);

		if (model_find(model, &iter, INSPECT_EXPR, reverse))
			inspect_hbit_update_iter(&iter, hb_mode);
		g_free(reverse);
	}

	g_free(expr);
	g_free(name);
}

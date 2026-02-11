row_inserted_cb (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, RBDisplayPageMenu *menu)
{
	int index;

	if (consider_page_iter (menu, iter) == FALSE) {
		return;
	}

	index = path_menu_index (menu, path);
	if (index != -1) {
		menu->priv->item_count++;
		g_menu_model_items_changed (G_MENU_MODEL (menu), index, 0, 1);
	}
}

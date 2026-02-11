count_items (RBDisplayPageMenu *menu, int upto)
{
	GtkTreeIter iter;
	int i;
	int c;

	if (get_page_iter (menu, &iter) == FALSE) {
		return 0;
	}

	i = 0;
	c = 0;
	while (c < upto) {
		RBDisplayPage *page;
		gtk_tree_model_get (menu->priv->real_model,
				    &iter,
				    RB_DISPLAY_PAGE_MODEL_COLUMN_PAGE, &page,
				    -1);

		if (consider_page (menu, page)) {
			i++;
		}
		g_object_unref (page);
		c++;
		if (!gtk_tree_model_iter_next (menu->priv->real_model, &iter))
			break;
	}

	return i;
}

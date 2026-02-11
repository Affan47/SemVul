brasero_medium_selection_get_media_num (BraseroMediumSelection *selector)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	int num = 0;

	model = gtk_combo_box_get_model (GTK_COMBO_BOX (selector));
	if (!gtk_tree_model_get_iter_first (model, &iter))
		return 0;

	do {
		BraseroMedium *medium;

		medium = NULL;
		gtk_tree_model_get (model, &iter,
				    MEDIUM_COL, &medium,
				    -1);
		if (!medium)
			continue;

		g_object_unref (medium);
		num ++;

	} while (gtk_tree_model_iter_next (model, &iter));

	return num;
}

brasero_layout_item_set_active (BraseroLayout *layout,
				BraseroLayoutItem *item)
{
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_combo_box_get_model (GTK_COMBO_BOX (layout->priv->combo));
	if (!gtk_tree_model_get_iter_first (model, &iter))
		return;

	do {
		BraseroLayoutItem *tree_item;

		gtk_tree_model_get (model, &iter,
				    ITEM_COL, &tree_item,
				    -1);

		if (tree_item == item) {
			BraseroLayoutObject *object;

			gtk_combo_box_set_active_iter (GTK_COMBO_BOX (layout->priv->combo), &iter);
			gtk_widget_show (item->widget);
			layout->priv->active_item = item;


			object = brasero_layout_item_get_object (item);
			brasero_layout_object_set_context (object, layout->priv->ctx_type);
			return;
		}
	} while (gtk_tree_model_iter_next (model, &iter));
}

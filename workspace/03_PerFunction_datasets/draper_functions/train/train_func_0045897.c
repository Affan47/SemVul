brasero_layout_add_source (BraseroLayout *layout,
			   GtkWidget *source,
			   const gchar *id,
			   const gchar *subtitle,
			   const gchar *icon_name,
			   BraseroLayoutType types)
{
	GtkWidget *pane;
	GtkTreeIter iter;
	GtkTreeModel *model;
	BraseroLayoutItem *item;

	pane = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
	gtk_widget_hide (pane);
	gtk_box_pack_end (GTK_BOX (pane), source, TRUE, TRUE, 0);
	g_signal_connect (pane,
			  "show",
			  G_CALLBACK (brasero_layout_page_showed),
			  layout);
	gtk_notebook_append_page (GTK_NOTEBOOK (layout->priv->notebook),
				  pane,
				  NULL);


	item = g_new0 (BraseroLayoutItem, 1);
	item->id = g_strdup (id);
	item->widget = pane;
	item->types = types;

	model = gtk_combo_box_get_model (GTK_COMBO_BOX (layout->priv->combo));
	model = gtk_tree_model_filter_get_model (GTK_TREE_MODEL_FILTER (model));
	gtk_list_store_append (GTK_LIST_STORE (model), &iter);
	gtk_list_store_set (GTK_LIST_STORE (model), &iter,
			    ICON_COL,icon_name,
			    TEXT_COL,subtitle,
			    ITEM_COL, item,
			    VISIBLE_COL, TRUE,
			    -1);

	if (gtk_tree_model_iter_n_children (model, NULL) > 1)
		gtk_widget_show (layout->priv->top_box);
}

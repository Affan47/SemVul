heap_view_init (HeapView* self)
{
  GtkTreeViewColumn* col = NULL;
  GtkCellRenderer* renderer = NULL;
  GtkTreeSelection* selection = NULL;

  self->priv = g_new0 (HeapViewPrivate, 1);


  self->priv->store = gtk_tree_store_new (COLUMN_NUMBER,
					  G_TYPE_INT,
					  G_TYPE_POINTER,
					  G_TYPE_STRING,
					  G_TYPE_STRING,
					  G_TYPE_STRING);

  gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (self->priv->store),
					COLUMN_NAME, GTK_SORT_ASCENDING);


  self->priv->view = GTK_TREE_VIEW (gtk_tree_view_new_with_model (GTK_TREE_MODEL (self->priv->store)));
  g_object_unref (self->priv->store);
  gtk_tree_view_set_headers_visible (self->priv->view, FALSE);


  col = gtk_tree_view_column_new ();
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_column_set_spacing (col, 0);
  gtk_tree_view_column_pack_start (col, renderer, FALSE);
  gtk_tree_view_column_add_attribute (col, renderer, "text", COLUMN_NAME);
  gtk_tree_view_column_set_alignment (col, 0.0);
  g_object_set (renderer, "xalign", 0.5, "ypad", 0, NULL);
  g_object_set (renderer, "weight", PANGO_WEIGHT_BOLD, NULL);
  gtk_tree_view_append_column (self->priv->view, col);
  gtk_tree_view_column_set_cell_data_func (col, renderer,
                                           hide_show_depending_on_type,
					   GINT_TO_POINTER (TYPE_GROUP), NULL);


  col = gtk_tree_view_column_new ();
  renderer = gm_cell_renderer_bitext_new ();
  gtk_tree_view_column_set_spacing (col, 0);
  gtk_tree_view_column_pack_start (col, renderer, FALSE);
  gtk_tree_view_column_add_attribute (col, renderer, "primary-text", COLUMN_NAME);
  gtk_tree_view_column_add_attribute (col, renderer, "secondary-text", COLUMN_STATUS);
  gtk_tree_view_column_set_alignment (col, 0.0);
  g_object_set (renderer, "xalign", 0.5, "ypad", 0, NULL);
  gtk_tree_view_append_column (self->priv->view, col);
  gtk_tree_view_column_set_cell_data_func (col, renderer,
                                           hide_show_depending_on_type,
					   GINT_TO_POINTER (TYPE_PRESENTITY), NULL);


  col = gtk_tree_view_column_new ();
  renderer = gtk_cell_renderer_pixbuf_new ();
  g_object_set (renderer, "yalign", 0.5, "xpad", 5, NULL);
  gtk_tree_view_column_pack_start (col, renderer, FALSE);
  gtk_tree_view_column_add_attribute (col, renderer,
				      "stock-id",
				      COLUMN_PRESENCE);
  gtk_tree_view_append_column (self->priv->view, col);
  gtk_tree_view_column_set_cell_data_func (col, renderer,
                                           hide_show_depending_on_type,
					   GINT_TO_POINTER (TYPE_PRESENTITY), NULL);


  selection = gtk_tree_view_get_selection (self->priv->view);
  gtk_tree_selection_set_mode (selection, GTK_SELECTION_SINGLE);
  g_signal_connect (selection, "changed", G_CALLBACK (on_selection_changed), self);


  g_signal_connect (self->priv->view, "event-after", G_CALLBACK (on_right_click_in_the_view), self);
}

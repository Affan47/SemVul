gth_window_set_n_pages (GthWindow *self,
			int        n_pages)
{
	int i;

	if (self->priv->n_pages != 0) {
		g_critical ("The number of pages of a GthWindow can be set only once.");
		return;
	}

	self->priv->n_pages = n_pages;

	self->priv->grid = gtk_grid_new ();
	gtk_widget_show (self->priv->grid);
	gtk_container_add (GTK_CONTAINER (self), self->priv->grid);

	self->priv->notebook = gtk_notebook_new ();
	gtk_style_context_remove_class (gtk_widget_get_style_context (self->priv->notebook), GTK_STYLE_CLASS_NOTEBOOK);
	gtk_notebook_set_show_tabs (GTK_NOTEBOOK (self->priv->notebook), FALSE);
	gtk_notebook_set_show_border (GTK_NOTEBOOK (self->priv->notebook), FALSE);
	gtk_widget_show (self->priv->notebook);
	gtk_grid_attach (GTK_GRID (self->priv->grid),
			 self->priv->notebook,
			 0, 2,
			 1, 1);

	self->priv->toolbars = g_new0 (GtkWidget *, n_pages);
	self->priv->contents = g_new0 (GtkWidget *, n_pages);

	for (i = 0; i < n_pages; i++) {
		GtkWidget *page;

		page = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
		gtk_widget_show (page);
		gtk_notebook_append_page (GTK_NOTEBOOK (self->priv->notebook),
					  page,
					  NULL);

		self->priv->toolbars[i] = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_widget_show (self->priv->toolbars[i]);
		gtk_box_pack_start (GTK_BOX (page), self->priv->toolbars[i], FALSE, FALSE, 0);

		self->priv->contents[i] = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_widget_hide (self->priv->contents[i]);
		gtk_box_pack_start (GTK_BOX (page), self->priv->contents[i], TRUE, TRUE, 0);
	}

	self->priv->window_size = g_new0 (GthWindowSize, n_pages);
	for (i = 0; i < n_pages; i++)
		self->priv->window_size[i].saved = FALSE;
}

save_html_index (gpointer data)
{
	GthWebExporter *self = data;
	GFile          *file;
	GFile          *relative_to;
	GError         *error = NULL;

	if (self->priv->saving_timeout != 0) {
		g_source_remove (self->priv->saving_timeout);
		self->priv->saving_timeout = 0;
	}

	if (self->priv->page >= self->priv->n_pages) {
		save_html_images (self);
		return FALSE;
	}


	gth_task_progress (GTH_TASK (self),
			   _("Saving HTML pages: Indexes"),
			   NULL,
			   FALSE,
			   (double) (self->priv->page + 1) / (self->priv->n_pages + 1));

	file = get_html_index_file (self, self->priv->page, self->priv->tmp_dir);
	relative_to = get_html_index_dir (self, self->priv->page, self->priv->target_dir);
	save_template (self, self->priv->index_template, GTH_TEMPLATE_TYPE_INDEX, file, relative_to, &error);

	g_object_unref (file);
	g_object_unref (relative_to);


	if (error != NULL) {
		cleanup_and_terminate (self, error);
		return FALSE;
	}

	self->priv->page++;
	self->priv->saving_timeout = g_idle_add (save_html_index, data);

	return FALSE;
}

gth_progress_dialog_finalize (GObject *base)
{
	GthProgressDialog *self = (GthProgressDialog *) base;

	if (self->priv->show_event != 0) {
		g_source_remove (self->priv->show_event);
		self->priv->show_event = 0;
	}

	G_OBJECT_CLASS (gth_progress_dialog_parent_class)->finalize (base);
}

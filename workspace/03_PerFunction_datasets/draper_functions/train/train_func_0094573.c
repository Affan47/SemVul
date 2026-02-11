gth_paned_set_position2 (GthPaned *self,
			 int       position)
{
	g_return_if_fail (GTH_IS_PANED (self));

	if (position >= 0) {
		self->priv->child2_size = position;
		self->priv->position2_set = TRUE;
	}
	else
		self->priv->position2_set = FALSE;

	g_object_notify (G_OBJECT (self), "position2");
	gtk_widget_queue_resize_no_redraw (GTK_WIDGET (self));
}

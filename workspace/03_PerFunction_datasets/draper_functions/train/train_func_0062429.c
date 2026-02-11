fr_file_selector_dialog_set_extra_widget (FrFileSelectorDialog *self,
					  GtkWidget            *extra_widget)
{
	if (self->priv->extra_widget != NULL)
		gtk_container_remove (GTK_CONTAINER (GET_WIDGET ("extra_widget_container")), self->priv->extra_widget);
	self->priv->extra_widget = extra_widget;
	if (self->priv->extra_widget != NULL)
		gtk_container_add (GTK_CONTAINER (GET_WIDGET ("extra_widget_container")), self->priv->extra_widget);
}

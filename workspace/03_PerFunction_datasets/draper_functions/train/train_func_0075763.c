_gth_dumb_notebook_grab_focus_child (GthDumbNotebook *notebook)
{
	GtkWidget *child;

	child = notebook->priv->current;
	if (child == NULL)
		return;

	if (GTK_IS_SCROLLED_WINDOW (notebook->priv->current)) {
		GList *list = gtk_container_get_children (GTK_CONTAINER (notebook->priv->current));
		if (list != NULL)
			child = list->data;
	}

	gtk_widget_grab_focus (child);
}

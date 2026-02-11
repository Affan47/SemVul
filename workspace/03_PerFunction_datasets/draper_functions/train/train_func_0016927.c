gnm_notebook_get_n_visible (GnmNotebook *nb)
{
	int count = 0;
	GList *l, *children = gtk_container_get_children (GTK_CONTAINER (nb));

	for (l = children; l; l = l->next) {
		GtkWidget *child = l->data;
		if (gtk_widget_get_visible (child))
			count++;
	}

	g_list_free (children);

	return count;
}

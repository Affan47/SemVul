totem_sidebar_get_current_page (Totem *totem)
{
	int current_page;
	GtkWidget *widget;

	if (totem->sidebar == NULL)
		return NULL;

	current_page = gtk_notebook_get_current_page (GTK_NOTEBOOK (totem->sidebar));
	widget = gtk_notebook_get_nth_page (GTK_NOTEBOOK (totem->sidebar), current_page);

	return g_strdup (g_object_get_data (G_OBJECT (widget), "sidebar-name"));
}

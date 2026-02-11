tag2_browser_unselected(GtkWidget * container)
{
	if (tag2_current)
		gtk_container_remove(GTK_CONTAINER(container), tag2_current);
	tag2_current = NULL;
}

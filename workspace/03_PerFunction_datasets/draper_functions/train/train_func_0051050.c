_gtk_paned_set_position2 (GtkPaned *paned,
			  int       pos)
{
	GtkWidget     *top_level;
	GtkAllocation  allocation;
	int            size;

	top_level = gtk_widget_get_toplevel (GTK_WIDGET (paned));
	if (! gtk_widget_is_toplevel (top_level))
		return;
	gtk_widget_get_allocation (top_level, &allocation);
	if (gtk_orientable_get_orientation (GTK_ORIENTABLE (paned)) == GTK_ORIENTATION_HORIZONTAL)
		size = allocation.width;
	else
		size = allocation.height;

	if (pos > 0)
		gtk_paned_set_position (paned, size - pos);
}

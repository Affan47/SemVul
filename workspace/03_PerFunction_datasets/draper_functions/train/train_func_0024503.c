glade_design_layout_deepest_widget_at_position (GtkContainer *toplevel,
						GtkContainer *container,
						gint top_x, gint top_y)
{
	GladeFindInContainerData data;
	GtkWidget *ret_widget = NULL;

	data.x = top_x;
	data.y = top_y;
	data.any = TRUE;
	data.toplevel = GTK_WIDGET (toplevel);
	data.found = NULL;

	gtk_container_forall (container, (GtkCallback)
			      glade_design_layout_find_inside_container, &data);

	if (data.found && GTK_IS_CONTAINER (data.found))
		ret_widget = glade_design_layout_deepest_widget_at_position
			(toplevel, GTK_CONTAINER (data.found), top_x, top_y);
	else if (data.found)
		ret_widget = data.found;
	else
		ret_widget = GTK_WIDGET (container);

	return ret_widget;
}

gth_image_navigator_draw_child (GtkWidget *child,
                                gpointer   user_data)
{
	DrawData *data = user_data;

	if (gtk_widget_get_child_visible (child))
		gtk_container_propagate_draw (GTK_CONTAINER (data->container),
					      child,
					      data->cr);
}

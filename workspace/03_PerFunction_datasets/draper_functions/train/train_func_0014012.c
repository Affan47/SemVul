change_window_status(void)
{
	gboolean visible;

	g_object_get(G_OBJECT(main_window), "visible", &visible, NULL);

	if (visible)
	{
		gtk_window_get_position(GTK_WINDOW(main_window), &current_x, &current_y);
		gtk_widget_hide(GTK_WIDGET(main_window));
	}
	else
	{
		gtk_widget_show(GTK_WIDGET(main_window));
		gtk_window_move(GTK_WINDOW(main_window), current_x, current_y);
	}
}

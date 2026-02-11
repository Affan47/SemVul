manage_window_destroy(GtkWidget *widget, gpointer data)
{


	if (focus_window == widget)
		focus_window = NULL;
}

menu_item_select_cb (GtkMenuItem *proxy,
		     glWindow    *window)
{
	GtkAction *action;
	char      *message;

	g_return_if_fail (window && GL_IS_WINDOW (window));
	g_return_if_fail (window->status_bar && GTK_IS_STATUSBAR (window->status_bar));

	action = g_object_get_data (G_OBJECT (proxy),  "gtk-action");
	g_return_if_fail (action != NULL);

	g_object_get (G_OBJECT (action), "tooltip", &message, NULL);
	if (message)
	{
		gtk_statusbar_push (GTK_STATUSBAR (window->status_bar),
				    window->menu_tips_context_id, message);
		g_free (message);
	}
}

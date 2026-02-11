menu_item_deselect_cb (GtkMenuItem *proxy,
		       glWindow    *window)
{
	g_return_if_fail (window && GL_IS_WINDOW (window));
	g_return_if_fail (window->status_bar && GTK_IS_STATUSBAR (window->status_bar));

	gtk_statusbar_pop (GTK_STATUSBAR (window->status_bar),
			   window->menu_tips_context_id);
}

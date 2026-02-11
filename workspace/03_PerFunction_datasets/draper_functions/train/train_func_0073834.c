panel_toplevel_move_resize_window (PanelToplevel *toplevel,
				   gboolean       move,
				   gboolean       resize)
{
	GtkWidget *widget;

	widget = GTK_WIDGET (toplevel);

	g_assert (gtk_widget_get_realized (widget));

	if (move && resize)
		gdk_window_move_resize (gtk_widget_get_window (widget),
					toplevel->priv->geometry.x,
					toplevel->priv->geometry.y,
					toplevel->priv->geometry.width,
					toplevel->priv->geometry.height);
	else if (move)
		gdk_window_move (gtk_widget_get_window (widget),
				 toplevel->priv->geometry.x,
				 toplevel->priv->geometry.y);
	else if (resize)
		gdk_window_resize (gtk_widget_get_window (widget),
				   toplevel->priv->geometry.width,
				   toplevel->priv->geometry.height);
}

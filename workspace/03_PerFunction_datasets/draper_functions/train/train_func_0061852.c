panel_toplevel_set_monitor_internal (PanelToplevel *toplevel,
				     int            monitor,
				     gboolean       force_resize)
{
	if (toplevel->priv->monitor == monitor)
		return;

	toplevel->priv->monitor = monitor;

	if (force_resize)
		gtk_widget_queue_resize (GTK_WIDGET (toplevel));
}

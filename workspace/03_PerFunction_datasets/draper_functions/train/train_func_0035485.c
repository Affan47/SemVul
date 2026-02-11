panel_toplevel_set_auto_hide (PanelToplevel *toplevel,
			      gboolean       auto_hide)
{
	g_return_if_fail (PANEL_IS_TOPLEVEL (toplevel));

	auto_hide = auto_hide != FALSE;

	if (toplevel->priv->auto_hide == auto_hide)
		return;

	toplevel->priv->auto_hide = auto_hide;

	if (toplevel->priv->auto_hide)
		panel_toplevel_queue_auto_hide (toplevel);
	else
		panel_toplevel_queue_auto_unhide (toplevel);

	if (panel_toplevel_update_struts (toplevel, FALSE))
		gtk_widget_queue_resize (GTK_WIDGET (toplevel));

	g_object_notify (G_OBJECT (toplevel), "auto-hide");
}

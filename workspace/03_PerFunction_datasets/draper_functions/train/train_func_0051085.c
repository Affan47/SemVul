panel_toplevel_set_auto_hide_size (PanelToplevel *toplevel,
				   int            auto_hide_size)
{
	g_return_if_fail (PANEL_IS_TOPLEVEL (toplevel));

	if (toplevel->priv->auto_hide_size == auto_hide_size)
		return;

	toplevel->priv->auto_hide_size = auto_hide_size;

	if (toplevel->priv->state == PANEL_STATE_AUTO_HIDDEN) {
		if (panel_toplevel_update_struts (toplevel, FALSE)) {
			if (toplevel->priv->animate) {
				panel_toplevel_unhide (toplevel);
				panel_toplevel_hide (toplevel, TRUE, -1);
			} else
				gtk_widget_queue_resize (GTK_WIDGET (toplevel));
		}
	}

	g_object_notify (G_OBJECT (toplevel), "auto-hide-size");
}

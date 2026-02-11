panel_toplevel_toggle_hidden (PanelToplevel *toplevel)
{
	if (toplevel->priv->state == PANEL_STATE_NORMAL)
		panel_toplevel_hide (toplevel, toplevel->priv->auto_hide, -1);
	else
		panel_toplevel_unhide (toplevel);

	return FALSE;
}

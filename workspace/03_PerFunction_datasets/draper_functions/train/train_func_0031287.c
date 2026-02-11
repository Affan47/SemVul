panel_widget_background_changed (PanelBackground *background,
				 PanelWidget     *panel)
{
	g_return_if_fail (PANEL_IS_WIDGET (panel));
	panel_toplevel_update_edges (panel->toplevel);
	g_signal_emit (G_OBJECT (panel),
		       panel_widget_signals [BACK_CHANGE_SIGNAL],
		       0);
}

panel_toplevel_realize (GtkWidget *widget)
{
	PanelToplevel *toplevel = (PanelToplevel *) widget;
	GdkWindow     *window;

	gtk_window_set_decorated (GTK_WINDOW (widget), FALSE);
	gtk_window_stick (GTK_WINDOW (widget));

	if (GTK_WIDGET_CLASS (panel_toplevel_parent_class)->realize)
		GTK_WIDGET_CLASS (panel_toplevel_parent_class)->realize (widget);

	window = gtk_widget_get_window (widget);

	panel_struts_set_window_hint (toplevel);
	panel_xutils_set_window_type (window, PANEL_XUTILS_TYPE_DOCK);

	gdk_window_set_group (window, window);
	gdk_window_set_geometry_hints (window, NULL, GDK_HINT_POS);

	panel_toplevel_initially_hide (toplevel);

	panel_toplevel_move_resize_window (toplevel, TRUE, TRUE);
}

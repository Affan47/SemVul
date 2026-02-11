background_changed (PanelBackgroundMonitor *monitor,
		    PanelBackground        *background)
{
	GdkPixbuf *tmp;

	tmp = background->desktop;

	background->desktop = panel_background_monitor_get_region (
					background->monitor,
					background->region.x,
					background->region.y,
					background->region.width,
					background->region.height);

	if (tmp)
		g_object_unref (tmp);

	panel_background_composite (background);
}

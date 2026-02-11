widget_auto_scroll_stop(GtkWidget *widget)
{
	AutoScrollData *sd;

	sd = g_object_get_data(G_OBJECT(widget), "autoscroll");
	if (!sd) return;
	g_object_set_data(G_OBJECT(widget), "autoscroll", NULL);

	if (sd->timer_id) g_source_remove(sd->timer_id);
	g_free(sd);
}

store_layout_timestamps_now (NautilusCanvasContainer *container)
{
	NautilusCanvasIcon *icon;
	GList *p;
	gboolean dummy;

	container->details->layout_timestamp = time (NULL);
	g_signal_emit (container,
		       signals[STORE_LAYOUT_TIMESTAMP], 0,
		       NULL, &container->details->layout_timestamp, &dummy);

	for (p = container->details->icons; p != NULL; p = p->next) {
		icon = p->data;

		g_signal_emit (container,
			       signals[STORE_LAYOUT_TIMESTAMP], 0,
			       icon->data, &container->details->layout_timestamp, &dummy);
	}
}

free_private (EventsPrivate *private)
{
	guint i;

	for (i = 0; i < private->notify_classes->len; i++) {
		TrackerClass *class = g_ptr_array_index (private->notify_classes, i);

		tracker_class_reset_pending_events (class);


		tracker_class_reset_ready_events (class);
	}

	g_ptr_array_unref (private->notify_classes);

	g_free (private);
}

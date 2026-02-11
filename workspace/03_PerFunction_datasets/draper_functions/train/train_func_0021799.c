tracker_events_reset_pending (void)
{
	guint i;

	g_return_if_fail (private != NULL);

	for (i = 0; i < private->notify_classes->len; i++) {
		TrackerClass *class = g_ptr_array_index (private->notify_classes, i);

		tracker_class_reset_pending_events (class);
	}

	private->frozen = FALSE;
}

tracker_events_init (void)
{
	TrackerClass **classes;
	guint length = 0, i;

	private = g_new0 (EventsPrivate, 1);

	classes = tracker_ontologies_get_classes (&length);

	private->notify_classes = g_ptr_array_sized_new (length);
	g_ptr_array_set_free_func (private->notify_classes, (GDestroyNotify) g_object_unref);

	for (i = 0; i < length; i++) {
		TrackerClass *class = classes[i];

		if (tracker_class_get_notify (class)) {
			g_ptr_array_add (private->notify_classes, g_object_ref (class));
		}
	}

}

tracker_events_add_delete (gint         graph_id,
                           gint         subject_id,
                           const gchar *subject,
                           gint         pred_id,
                           gint         object_id,
                           const gchar *object,
                           GPtrArray   *rdf_types)
{
	guint i;

	g_return_if_fail (rdf_types != NULL);
	g_return_if_fail (private != NULL);

	if (private->frozen) {
		return;
	}

	for (i = 0; i < rdf_types->len; i++) {
		if (tracker_class_get_notify (rdf_types->pdata[i])) {
			tracker_class_add_delete_event (rdf_types->pdata[i],
			                                graph_id,
			                                subject_id,
			                                pred_id,
			                                object_id);
			private->total++;
		}
	}
}

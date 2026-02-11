e_data_cal_respond_create_objects (EDataCal *cal,
                                   guint32 opid,
                                   GError *error,
                                   const GSList *uids,
                                   GSList *new_components)
{
	ECalBackend *backend;
	GSimpleAsyncResult *simple;
	GQueue *queue = NULL;

	g_return_if_fail (E_IS_DATA_CAL (cal));

	backend = e_data_cal_ref_backend (cal);
	g_return_if_fail (backend != NULL);

	simple = e_cal_backend_prepare_for_completion (backend, opid, &queue);
	g_return_if_fail (simple != NULL);
	g_return_if_fail (queue != NULL);


	g_prefix_error (&error, "%s", _("Cannot create calendar object: "));

	if (error == NULL) {
		GQueue *inner_queue;
		GSList *list, *link;

		inner_queue = g_queue_new ();

		list = (GSList *) uids;

		for (link = list; link != NULL; link = g_slist_next (link))
			g_queue_push_tail (inner_queue, g_strdup (link->data));

		g_queue_push_tail (queue, inner_queue);

		inner_queue = g_queue_new ();

		list = (GSList *) new_components;

		for (link = list; link != NULL; link = g_slist_next (link))
			g_queue_push_tail (
				inner_queue,
				g_object_ref (link->data));

		g_queue_push_tail (queue, inner_queue);

	} else {
		g_simple_async_result_take_error (simple, error);
	}

	g_simple_async_result_complete_in_idle (simple);

	g_object_unref (simple);
	g_object_unref (backend);
}

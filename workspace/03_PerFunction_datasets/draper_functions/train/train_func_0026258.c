e_cal_client_generate_instances_for_object (ECalClient *client,
                                            icalcomponent *icalcomp,
                                            time_t start,
                                            time_t end,
                                            GCancellable *cancellable,
                                            ECalRecurInstanceFn cb,
                                            gpointer cb_data,
                                            GDestroyNotify destroy_cb_data)
{
	ECalComponent *comp;
	const gchar *uid;
	ECalComponentDateTime datetime;
	icaltimezone *start_zone = NULL, *end_zone = NULL;
	gboolean is_single_instance = FALSE;
	struct get_objects_async_data *goad;
	GCancellable *use_cancellable;

	g_return_if_fail (E_IS_CAL_CLIENT (client));

	g_return_if_fail (start >= 0);
	g_return_if_fail (end >= 0);
	g_return_if_fail (cb != NULL);

	comp = e_cal_component_new ();
	e_cal_component_set_icalcomponent (comp, icalcomponent_new_clone (icalcomp));

	if (!e_cal_component_has_recurrences (comp))
		is_single_instance = TRUE;


	if (is_single_instance || e_client_check_capability (E_CLIENT (client), CAL_STATIC_CAPABILITY_RECURRENCES_NO_MASTER)) {

		(* cb)  (comp,
			icaltime_as_timet_with_zone (
				icalcomponent_get_dtstart (icalcomp),
				client->priv->default_zone),
			icaltime_as_timet_with_zone (
				icalcomponent_get_dtend (icalcomp),
				client->priv->default_zone),
			cb_data);
		g_object_unref (comp);

		if (destroy_cb_data)
			destroy_cb_data (cb_data);
		return;
	}

	e_cal_component_get_uid (comp, &uid);


	e_cal_component_get_dtstart (comp, &datetime);
	if (datetime.tzid)
		e_cal_client_get_timezone_sync (
			client, datetime.tzid, &start_zone, NULL, NULL);
	else
		start_zone = NULL;
	e_cal_component_free_datetime (&datetime);


	e_cal_component_get_dtend (comp, &datetime);
	if (datetime.tzid)
		e_cal_client_get_timezone_sync (
			client, datetime.tzid, &end_zone, NULL, NULL);
	else
		end_zone = NULL;
	e_cal_component_free_datetime (&datetime);

	use_cancellable = cancellable;
	if (!use_cancellable)
		use_cancellable = g_cancellable_new ();

	goad = g_new0 (struct get_objects_async_data, 1);
	goad->cancellable = g_object_ref (use_cancellable);
	goad->client = g_object_ref (client);
	goad->start = start;
	goad->end = end;
	goad->cb = cb;
	goad->cb_data = cb_data;
	goad->destroy_cb_data = destroy_cb_data;
	goad->start_zone = start_zone;
	goad->end_zone = end_zone;
	goad->comp = comp;
	goad->uid = g_strdup (uid);

	get_objects_async (generate_instances_for_object_got_objects_cb, goad);

	if (use_cancellable != cancellable)
		g_object_unref (use_cancellable);
}

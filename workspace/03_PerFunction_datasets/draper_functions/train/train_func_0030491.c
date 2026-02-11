do_receive_objects (ECalBackendSync *backend,
                    EDataCal *cal,
                    GCancellable *cancellable,
                    const gchar *calobj,
                    GError **perror)
{
	ECalBackendCalDAV        *cbdav;
	icalcomponent            *icomp;
	icalcomponent_kind        kind;
	icalproperty_method       tmethod;
	gboolean                  online;
	GSList                   *objects, *iter;
	GError *err = NULL;

	cbdav = E_CAL_BACKEND_CALDAV (backend);

	if (!check_state (cbdav, &online, perror))
		return;

	icomp = icalparser_parse_string (calobj);


	if (icomp == NULL) {
		g_propagate_error (perror, EDC_ERROR (InvalidObject));
		return;
	}

	kind = e_cal_backend_get_kind (E_CAL_BACKEND (backend));
	extract_objects (icomp, kind, &objects, &err);

	if (err) {
		icalcomponent_free (icomp);
		g_propagate_error (perror, err);
		return;
	}


	extract_timezones (cbdav, icomp);

	tmethod = icalcomponent_get_method (icomp);

	for (iter = objects; iter && !err; iter = iter->next) {
		icalcomponent       *scomp;
		ECalComponent       *ecomp;
		icalproperty_method  method;

		scomp = (icalcomponent *) iter->data;
		ecomp = e_cal_component_new ();

		e_cal_component_set_icalcomponent (ecomp, scomp);

		if (icalcomponent_get_first_property (scomp, ICAL_METHOD_PROPERTY)) {
			method = icalcomponent_get_method (scomp);
		} else {
			method = tmethod;
		}

		process_object (cbdav, ecomp, online, method, cancellable, &err);
		g_object_unref (ecomp);
	}

	g_slist_free (objects);

	icalcomponent_free (icomp);

	if (err)
		g_propagate_error (perror, err);
}

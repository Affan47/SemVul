e_cal_backend_cache_get_components (ECalBackendCache *cache)
{
	gchar *comp_str;
	GSList *l;
	GList *list = NULL;
	icalcomponent *icalcomp;
	ECalComponent *comp = NULL;


	g_return_val_if_fail (E_IS_CAL_BACKEND_CACHE (cache), NULL);
	l = e_file_cache_get_objects (E_FILE_CACHE (cache));
	if (!l)
		return NULL;
	for (; l != NULL; l = g_slist_next (l)) {
		comp_str = l->data;
		if (comp_str) {
			icalcomp = icalparser_parse_string (comp_str);
			if (icalcomp) {
				icalcomponent_kind kind;

				kind = icalcomponent_isa (icalcomp);
				if (kind == ICAL_VEVENT_COMPONENT || kind == ICAL_VTODO_COMPONENT || kind == ICAL_VJOURNAL_COMPONENT) {
					comp = e_cal_component_new ();
					if (e_cal_component_set_icalcomponent (comp, icalcomp))
						list = g_list_prepend (list, comp);
					else {
						icalcomponent_free (icalcomp);
						g_object_unref (comp);
					}
				} else
					icalcomponent_free (icalcomp);
			}
		}

	}

	return list;
}

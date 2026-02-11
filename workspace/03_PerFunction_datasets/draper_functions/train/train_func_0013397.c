put_server_comp_to_cache (ECalBackendCalDAV *cbdav,
                          icalcomponent *icomp,
                          const gchar *href,
                          const gchar *etag,
                          GTree *c_uid2complist)
{
	icalcomponent_kind kind;
	ECalBackend *cal_backend;

	g_return_if_fail (cbdav != NULL);
	g_return_if_fail (icomp != NULL);

	cal_backend = E_CAL_BACKEND (cbdav);
	kind = icalcomponent_isa (icomp);
	extract_timezones (cbdav, icomp);

	if (kind == ICAL_VCALENDAR_COMPONENT) {
		icalcomponent *subcomp;

		kind = e_cal_backend_get_kind (cal_backend);

		for (subcomp = icalcomponent_get_first_component (icomp, kind);
		     subcomp;
		     subcomp = icalcomponent_get_next_component (icomp, kind)) {
			ECalComponent *new_comp, *old_comp;

			convert_to_url_attachment (cbdav, subcomp);
			new_comp = e_cal_component_new ();
			if (e_cal_component_set_icalcomponent (new_comp, icalcomponent_new_clone (subcomp))) {
				const gchar *uid = NULL;
				struct cache_comp_list *ccl;

				e_cal_component_get_uid (new_comp, &uid);
				if (!uid) {
					g_warning ("%s: no UID on component!", G_STRFUNC);
					g_object_unref (new_comp);
					continue;
				}

				if (href)
					ecalcomp_set_href (new_comp, href);
				if (etag)
					ecalcomp_set_etag (new_comp, etag);

				old_comp = NULL;
				if (c_uid2complist) {
					ccl = g_tree_lookup (c_uid2complist, uid);
					if (ccl) {
						gchar *nc_rid = e_cal_component_get_recurid_as_string (new_comp);
						GSList *p;

						for (p = ccl->slist; p && !old_comp; p = p->next) {
							gchar *oc_rid;

							old_comp = p->data;

							oc_rid = e_cal_component_get_recurid_as_string (old_comp);
							if (g_strcmp0 (nc_rid, oc_rid) != 0) {
								old_comp = NULL;
							}

							g_free (oc_rid);
						}

						g_free (nc_rid);
					}
				}

				put_component_to_store (cbdav, new_comp);

				if (old_comp == NULL) {
					e_cal_backend_notify_component_created (cal_backend, new_comp);
				} else {
					e_cal_backend_notify_component_modified (cal_backend, old_comp, new_comp);

					if (ccl)
						ccl->slist = g_slist_remove (ccl->slist, old_comp);
					g_object_unref (old_comp);
				}
			}

			g_object_unref (new_comp);
		}
	}
}

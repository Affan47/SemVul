e_cal_backend_file_get_backend_property (ECalBackend *backend,
                                         const gchar *prop_name)
{
	g_return_val_if_fail (prop_name != NULL, FALSE);

	if (g_str_equal (prop_name, CLIENT_BACKEND_PROPERTY_CAPABILITIES)) {
		return g_strjoin (
			",",
			CAL_STATIC_CAPABILITY_NO_EMAIL_ALARMS,
			CAL_STATIC_CAPABILITY_NO_THISANDFUTURE,
			CAL_STATIC_CAPABILITY_DELEGATE_SUPPORTED,
			CAL_STATIC_CAPABILITY_REMOVE_ONLY_THIS,
			CAL_STATIC_CAPABILITY_NO_THISANDPRIOR,
			CAL_STATIC_CAPABILITY_BULK_ADDS,
			CAL_STATIC_CAPABILITY_BULK_MODIFIES,
			CAL_STATIC_CAPABILITY_BULK_REMOVES,
			CAL_STATIC_CAPABILITY_ALARM_DESCRIPTION,
			NULL);

	} else if (g_str_equal (prop_name, CAL_BACKEND_PROPERTY_CAL_EMAIL_ADDRESS) ||
		   g_str_equal (prop_name, CAL_BACKEND_PROPERTY_ALARM_EMAIL_ADDRESS)) {


		return NULL;

	} else if (g_str_equal (prop_name, CAL_BACKEND_PROPERTY_DEFAULT_OBJECT)) {
		ECalComponent *comp;
		gchar *prop_value;

		comp = e_cal_component_new ();

		switch (e_cal_backend_get_kind (E_CAL_BACKEND (backend))) {
		case ICAL_VEVENT_COMPONENT:
			e_cal_component_set_new_vtype (comp, E_CAL_COMPONENT_EVENT);
			break;
		case ICAL_VTODO_COMPONENT:
			e_cal_component_set_new_vtype (comp, E_CAL_COMPONENT_TODO);
			break;
		case ICAL_VJOURNAL_COMPONENT:
			e_cal_component_set_new_vtype (comp, E_CAL_COMPONENT_JOURNAL);
			break;
		default:
			g_object_unref (comp);
			return NULL;
		}

		prop_value = e_cal_component_get_as_string (comp);

		g_object_unref (comp);

		return prop_value;

	} else if (g_str_equal (prop_name, CAL_BACKEND_PROPERTY_REVISION)) {
		icalproperty *prop;
		const gchar *revision = NULL;


		prop = ensure_revision (E_CAL_BACKEND_FILE (backend));
		if (prop != NULL)
			revision = icalproperty_get_x (prop);

		return g_strdup (revision);
	}


	return E_CAL_BACKEND_CLASS (e_cal_backend_file_parent_class)->
		get_backend_property (backend, prop_name);
}

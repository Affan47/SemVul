ensure_alarm_properties_cb (gpointer key,
                            gpointer value,
                            gpointer data)
{
	ECalComponent *comp;
	ECalComponentPrivate *priv;
	icalcomponent *alarm;
	icalproperty *prop;
	enum icalproperty_action action;
	const gchar *str;

	alarm = value;

	comp = E_CAL_COMPONENT (data);
	priv = comp->priv;

	prop = icalcomponent_get_first_property (alarm, ICAL_ACTION_PROPERTY);
	if (!prop)
		return;

	action = icalproperty_get_action (prop);

	switch (action) {
	case ICAL_ACTION_DISPLAY:

		prop = icalcomponent_get_first_property (alarm, ICAL_DESCRIPTION_PROPERTY);
		if (prop) {
			if (priv->summary.prop) {
				icalproperty *xprop;

				xprop = icalcomponent_get_first_property (alarm, ICAL_X_PROPERTY);
				while (xprop) {
					str = icalproperty_get_x_name (xprop);
					if (!strcmp (str, "X-EVOLUTION-NEEDS-DESCRIPTION")) {
						icalproperty_set_description (prop, icalproperty_get_summary (priv->summary.prop));

						icalcomponent_remove_property (alarm, xprop);
						icalproperty_free (xprop);
						break;
					}

					xprop = icalcomponent_get_next_property (alarm, ICAL_X_PROPERTY);
				}

				break;
			}
		}

		if (!priv->summary.prop) {
			str = _("Untitled appointment");


			prop = icalproperty_new_x ("1");
			icalproperty_set_x_name (prop, "X-EVOLUTION-NEEDS-DESCRIPTION");
			icalcomponent_add_property (alarm, prop);
		} else
			str = icalproperty_get_summary (priv->summary.prop);

		prop = icalproperty_new_description (str);
		icalcomponent_add_property (alarm, prop);

		break;

	default:
		break;

	}
}

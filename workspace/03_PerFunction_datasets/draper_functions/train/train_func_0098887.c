handle_vc_property_changed(DBusConnection *conn,
					DBusMessage *msg, void *data)
{
	struct voice_call *vc = data;
	const char *obj_path = dbus_message_get_path(msg);
	DBusMessageIter iter, sub;
	const char *property, *state;

	DBG("path %s", obj_path);

	dbus_message_iter_init(msg, &iter);

	if (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_STRING) {
		error("Unexpected signature in vc PropertyChanged signal");
		return TRUE;
	}

	dbus_message_iter_get_basic(&iter, &property);
	DBG("property %s", property);

	dbus_message_iter_next(&iter);
	dbus_message_iter_recurse(&iter, &sub);
	if (g_str_equal(property, "State")) {
		dbus_message_iter_get_basic(&sub, &state);
		DBG("State %s", state);
		if (g_str_equal(state, "disconnected")) {
			calls = g_slist_remove(calls, vc);
			call_free(vc);
		} else if (g_str_equal(state, "active")) {
			telephony_update_indicator(ofono_indicators,
							"call", EV_CALL_ACTIVE);
			telephony_update_indicator(ofono_indicators,
							"callsetup",
							EV_CALLSETUP_INACTIVE);
			if (vc->status == CALL_STATUS_INCOMING)
				telephony_calling_stopped_ind();
			vc->status = CALL_STATUS_ACTIVE;
		} else if (g_str_equal(state, "alerting")) {
			telephony_update_indicator(ofono_indicators,
					"callsetup", EV_CALLSETUP_ALERTING);
			vc->status = CALL_STATUS_ALERTING;
			vc->originating = TRUE;
		} else if (g_str_equal(state, "incoming")) {

			telephony_update_indicator(ofono_indicators,
					"callsetup", EV_CALLSETUP_INCOMING);
			telephony_incoming_call_ind(vc->number,
						NUMBER_TYPE_TELEPHONY);
			vc->status = CALL_STATUS_INCOMING;
			vc->originating = FALSE;
		} else if (g_str_equal(state, "held")) {
			vc->status = CALL_STATUS_HELD;
			if (find_vc_without_status(CALL_STATUS_HELD))
				telephony_update_indicator(ofono_indicators,
							"callheld",
							EV_CALLHELD_MULTIPLE);
			else
				telephony_update_indicator(ofono_indicators,
							"callheld",
							EV_CALLHELD_ON_HOLD);
		}
	} else if (g_str_equal(property, "Multiparty")) {
		dbus_bool_t multiparty;

		dbus_message_iter_get_basic(&sub, &multiparty);
		DBG("Multiparty %s", multiparty ? "True" : "False");
		vc->conference = multiparty;
	}

	return TRUE;
}

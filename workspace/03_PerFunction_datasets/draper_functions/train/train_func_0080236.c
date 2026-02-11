request_resubmit(DBusConnection *conn, DBusMessage *msg,
		 struct cm_client_info *ci, struct cm_context *ctx)
{
	DBusMessage *rep;
	struct cm_store_entry *entry;
	const char *propname[2];
	char *path;

	entry = get_entry_for_request_message(msg, ctx);
	if (entry == NULL) {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
	rep = dbus_message_new_method_return(msg);
	if (rep != NULL) {
		if (cm_stop_one(ctx, entry->cm_nickname)) {


			if (entry->cm_key_type.cm_key_size == 0) {
				entry->cm_state = CM_NEED_KEY_PAIR;
			} else {
				entry->cm_state = CM_NEED_CSR;
			}

			propname[0] = CM_DBUS_PROP_STATUS;
			propname[1] = NULL;
			path = talloc_asprintf(entry, "%s/%s",
					       CM_DBUS_REQUEST_PATH,
					       entry->cm_busname);
			cm_tdbush_property_emit_changed(ctx, path,
							CM_DBUS_REQUEST_INTERFACE,
							propname);
			talloc_free(path);
			if (cm_start_one(ctx, entry->cm_nickname)) {
				cm_tdbusm_set_b(rep, TRUE);
			} else {
				cm_tdbusm_set_b(rep, FALSE);
			}
		} else {
			cm_tdbusm_set_b(rep, FALSE);
		}
		dbus_connection_send(conn, rep, NULL);
		dbus_message_unref(rep);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return send_internal_request_error(conn, msg);
	}
}

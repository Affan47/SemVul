request_get_csr_info(DBusConnection *conn, DBusMessage *msg,
		     struct cm_client_info *ci, struct cm_context *ctx)
{
	DBusMessage *rep;
	struct cm_store_entry *entry;
	char **eku;
	entry = get_entry_for_request_message(msg, ctx);
	if (entry == NULL) {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
	rep = dbus_message_new_method_return(msg);
	if (rep != NULL) {
		if (entry->cm_csr != NULL) {
			eku = eku_splitv(entry, entry->cm_template_eku);
			cm_tdbusm_set_sasasasnas(rep,
						 entry->cm_template_subject,
						 (const char **) entry->cm_template_email,
						 (const char **) entry->cm_template_hostname,
						 (const char **) entry->cm_template_principal,
						 ku_from_string(entry->cm_template_ku),
						 (const char **) eku);
			talloc_free(eku);
		}
		dbus_connection_send(conn, rep, NULL);
		dbus_message_unref(rep);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return send_internal_request_error(conn, msg);
	}
}

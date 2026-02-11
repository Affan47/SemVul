update_xml_record(DBusConnection *conn,
				DBusMessage *msg,
				struct service_adapter *serv_adapter)
{
	struct record_data *user_record;
	sdp_record_t *sdp_record;
	const char *record;
	dbus_uint32_t handle;
	int len;

	if (dbus_message_get_args(msg, NULL,
				DBUS_TYPE_UINT32, &handle,
				DBUS_TYPE_STRING, &record,
				DBUS_TYPE_INVALID) == FALSE)
		return NULL;

	len = (record ? strlen(record) : 0);
	if (len == 0)
		return btd_error_invalid_args(msg);

	user_record = find_record(serv_adapter, handle,
				dbus_message_get_sender(msg));
	if (!user_record)
		return btd_error_not_available(msg);

	sdp_record = sdp_xml_parse_record(record, len);
	if (!sdp_record) {
		error("Parsing of XML service record failed");
		return btd_error_failed(msg,
					"Parsing of XML service record failed");
	}

	return update_record(conn, msg, serv_adapter, handle, sdp_record);
}

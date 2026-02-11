csd_init(void)
{
	dbus_uint32_t location;
	uint8_t pb_type, location_type;
	int ret;

	ret = send_method_call(CSD_CALL_BUS_NAME, CSD_CALL_PATH,
				CSD_CALL_INTERFACE, "GetCallInfoAll",
				call_info_reply, NULL, DBUS_TYPE_INVALID);
	if (ret < 0) {
		error("Unable to sent GetCallInfoAll method call");
		return;
	}

	get_calls_active = TRUE;

	pb_type = SIM_PHONEBOOK_TYPE_MSISDN;
	location = PHONEBOOK_INDEX_FIRST_ENTRY;
	location_type = SIM_PHONEBOOK_LOCATION_NEXT;

	ret = send_method_call(SIM_PHONEBOOK_BUS_NAME, SIM_PHONEBOOK_PATH,
				SIM_PHONEBOOK_INTERFACE, "read",
				phonebook_read_reply, &msisdn,
				DBUS_TYPE_BYTE, &pb_type,
				DBUS_TYPE_INT32, &location,
				DBUS_TYPE_BYTE, &location_type,
				DBUS_TYPE_INVALID);
	if (ret < 0) {
		error("Unable to send " SIM_PHONEBOOK_INTERFACE ".read()");
		return;
	}

	pb_type = SIM_PHONEBOOK_TYPE_MBDN;
	location = PHONEBOOK_INDEX_FIRST_ENTRY;
	location_type = SIM_PHONEBOOK_LOCATION_NEXT;

	ret = send_method_call(SIM_PHONEBOOK_BUS_NAME, SIM_PHONEBOOK_PATH,
				SIM_PHONEBOOK_INTERFACE, "read",
				phonebook_read_reply, &vmbx,
				DBUS_TYPE_BYTE, &pb_type,
				DBUS_TYPE_INT32, &location,
				DBUS_TYPE_BYTE, &location_type,
				DBUS_TYPE_INVALID);
	if (ret < 0) {
		error("Unable to send " SIM_PHONEBOOK_INTERFACE ".read()");
		return;
	}
}

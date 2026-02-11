telephony_dial_number_req(void *telephony_device, const char *number)
{
	const char *clir;
	int ret;

	DBG("telephony-ofono: dial request to %s", number);

	if (!modem_obj_path) {
		telephony_dial_number_rsp(telephony_device,
					CME_ERROR_AG_FAILURE);
		return;
	}

	if (!strncmp(number, "*31#", 4)) {
		number += 4;
		clir = "enabled";
	} else if (!strncmp(number, "#31#", 4)) {
		number += 4;
		clir =  "disabled";
	} else
		clir = "default";

	ret = send_method_call(OFONO_BUS_NAME, modem_obj_path,
			OFONO_VCMANAGER_INTERFACE,
                        "Dial", NULL, NULL,
			DBUS_TYPE_STRING, &number,
			DBUS_TYPE_STRING, &clir,
			DBUS_TYPE_INVALID);

	if (ret < 0)
		telephony_dial_number_rsp(telephony_device,
			CME_ERROR_AG_FAILURE);
	else
		telephony_dial_number_rsp(telephony_device, CME_ERROR_NONE);
}

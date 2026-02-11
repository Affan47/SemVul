append_security(DBusMessageIter *iter, void *user_data)
{
	struct connman_service *service = user_data;
	const char *str;

	str = security2string(service->security);
	if (str != NULL)
		dbus_message_iter_append_basic(iter,
				DBUS_TYPE_STRING, &str);


	if (service->wps == TRUE) {
		switch (service->security) {
		case CONNMAN_SERVICE_SECURITY_PSK:
		case CONNMAN_SERVICE_SECURITY_WPA:
		case CONNMAN_SERVICE_SECURITY_RSN:
			str = "wps";
			dbus_message_iter_append_basic(iter,
			        DBUS_TYPE_STRING, &str);
			break;
		case CONNMAN_SERVICE_SECURITY_UNKNOWN:
		case CONNMAN_SERVICE_SECURITY_NONE:
		case CONNMAN_SERVICE_SECURITY_WEP:
		case CONNMAN_SERVICE_SECURITY_8021X:
			break;
		}
	}
}

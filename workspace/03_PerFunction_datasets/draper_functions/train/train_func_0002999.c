add_network_security_proto(DBusMessageIter *dict,
						GSupplicantSSID *ssid)
{
	unsigned int protocol, i;
	char *proto;
	char *protos[3];

	protocol = ssid->protocol;

	if (protocol == 0)
		return;

	i = 0;

	if (protocol & G_SUPPLICANT_PROTO_RSN)
		protos[i++] = "RSN";

	if (protocol & G_SUPPLICANT_PROTO_WPA)
		protos[i++] = "WPA";

	protos[i] = NULL;

	proto = g_strjoinv(" ", protos);

	SUPPLICANT_DBG("proto %s", proto);

	supplicant_dbus_dict_append_basic(dict, "proto",
						DBUS_TYPE_STRING,
						&proto);

	g_free(proto);
}

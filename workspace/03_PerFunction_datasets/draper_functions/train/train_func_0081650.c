bearer2service(const char *bearer, enum connman_service_type *type)
{
	if (g_strcmp0(bearer, "ethernet") == 0)
		*type = CONNMAN_SERVICE_TYPE_ETHERNET;
	else if (g_strcmp0(bearer, "wifi") == 0)
		*type = CONNMAN_SERVICE_TYPE_WIFI;
	else if (g_strcmp0(bearer, "bluetooth") == 0)
		*type = CONNMAN_SERVICE_TYPE_BLUETOOTH;
	else if (g_strcmp0(bearer, "cellular") == 0)
		*type = CONNMAN_SERVICE_TYPE_CELLULAR;
	else if (g_strcmp0(bearer, "vpn") == 0)
		*type = CONNMAN_SERVICE_TYPE_VPN;
	else if (g_strcmp0(bearer, "*") == 0)
		*type = CONNMAN_SERVICE_TYPE_UNKNOWN;
	else
		return -EINVAL;

	return 0;
}

g_supplicant_interface_get_wps_ssid(GSupplicantInterface *interface,
							unsigned int *ssid_len)
{
	if (ssid_len == NULL)
		return NULL;

	if (interface == NULL || interface->wps_cred.ssid == NULL) {
		*ssid_len = 0;
		return NULL;
	}

	*ssid_len = interface->wps_cred.ssid_len;
	return interface->wps_cred.ssid;
}

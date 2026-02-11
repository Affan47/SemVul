g_supplicant_interface_set_country(GSupplicantInterface *interface,
					GSupplicantCountryCallback callback,
							const char *alpha2,
							void *user_data)
{
	struct supplicant_regdom *regdom;

	regdom = dbus_malloc0(sizeof(*regdom));
	if (regdom == NULL)
		return -ENOMEM;

	regdom->callback = callback;
	regdom->alpha2 = alpha2;
	regdom->user_data = user_data;

	return supplicant_dbus_property_set(interface->path,
				SUPPLICANT_INTERFACE ".Interface",
				"Country", DBUS_TYPE_STRING_AS_STRING,
				country_params, country_result,
					regdom);
}

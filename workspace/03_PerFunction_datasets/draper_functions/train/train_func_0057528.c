country_result(const char *error,
				DBusMessageIter *iter, void *user_data)
{
	struct supplicant_regdom *regdom = user_data;
	int result = 0;

	SUPPLICANT_DBG("Country setting result");

	if (user_data == NULL)
		return;

	if (error != NULL) {
		SUPPLICANT_DBG("Country setting failure %s", error);
		result = -EINVAL;
	}

	if (regdom->callback)
		regdom->callback(result, regdom->alpha2,
					(void *) regdom->user_data);

	g_free(regdom);
}

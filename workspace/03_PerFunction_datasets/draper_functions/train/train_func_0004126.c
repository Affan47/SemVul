xlat_config(void *instance, REQUEST *request,
			  char *fmt, char *out,
			  size_t outlen,
			  RADIUS_ESCAPE_STRING func)
{
	const char *value;
	CONF_PAIR *cp;
	CONF_ITEM *ci;
	char buffer[1024];

	request = request;
	instance = instance;


	if (!radius_xlat(buffer, sizeof(buffer), fmt, request, config_escape_func)) {
		return 0;
	}

	ci = cf_reference_item(request->root->config,
			       request->root->config, buffer);
	if (!ci || !cf_item_is_pair(ci)) {
		*out = '\0';
		return 0;
	}

	cp = cf_itemtopair(ci);


	value = cf_pair_value(cp);
	if (value) {
		if (outlen > strlen(value)) {
			outlen = strlen(value) + 1;
		}
	}

	return func(out, outlen, value);
}

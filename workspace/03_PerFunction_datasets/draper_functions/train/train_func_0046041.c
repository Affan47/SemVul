get_conf_setting(struct conf* cf,
                             const char* name, const char* defvalue)
{
	int i;
	const char* val;

	for (i=2; i>=0; i--) {
		val = egdi_get_setting_value(&cf->config[i], name);
		if (val)
			return val;
	}

	return defvalue;
}

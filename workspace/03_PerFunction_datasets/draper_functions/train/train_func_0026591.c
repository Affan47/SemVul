expiration_instantiate(CONF_SECTION *conf, void **instance)
{
	rlm_expiration_t *data;


	data = rad_malloc(sizeof(*data));
	if (!data) {
		radlog(L_ERR, "rlm_expiration: rad_malloc() failed.");
		return -1;
	}
	memset(data, 0, sizeof(*data));


	if (cf_section_parse(conf, data, module_config) < 0) {
		free(data);
		radlog(L_ERR, "rlm_expiration: Configuration parsing failed.");
		return -1;
	}


	paircompare_register(PW_EXPIRATION, 0, expirecmp, data);

	*instance = data;

	return 0;
}

i18nInit() {
	i18nResource = res_find_and_init_resource(PROPERTYDIR, RESOURCE_FILE);

	if (getenv("HTTP_ACCEPT_LANGUAGE")) {
		acceptLanguage = getenv("HTTP_ACCEPT_LANGUAGE");
	}
}

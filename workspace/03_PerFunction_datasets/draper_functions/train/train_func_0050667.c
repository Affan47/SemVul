isns_init_names(void)
{
	if (isns_config.ic_host_name == NULL) {
		char	namebuf[1024], *fqdn;

		if (gethostname(namebuf, sizeof(namebuf)) < 0) {
			isns_error("gehostname: %m\n");
			return 0;
		}
		fqdn = isns_get_canon_name(namebuf);
		if (fqdn == NULL) {


			isns_error("Unable to get fully qualified hostname\n");
			return 0;
		}
		isns_config.ic_host_name = fqdn;
	}

	if (isns_config.ic_auth_name == NULL) {
		isns_config.ic_auth_name = isns_config.ic_host_name;
	}

	if (isns_config.ic_entity_name == NULL) {
		isns_config.ic_entity_name = isns_config.ic_auth_name;
	}

	if (isns_config.ic_source_name == NULL) {
		isns_config.ic_source_name = __revert_fqdn(DUMMY_IQN_PREFIX,
				isns_config.ic_host_name,
				isns_config.ic_source_suffix);
		if (isns_config.ic_source_name == NULL) {
			isns_error("Unable to build source name\n");
			return 0;
		}
	}

	return 1;
}

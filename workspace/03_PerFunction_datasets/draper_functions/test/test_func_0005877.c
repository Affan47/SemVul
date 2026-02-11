main_fetch_and_apply_config(struct config* config, struct string* oldconfig)


{
	int err;
	struct string http_response;

	log_debug("Fetching information.");

	string_init(&http_response, 4096, 512);

	err = main_request_config(config, &http_response);
	if (err < 1) {

		string_free(&http_response);
		if (err < 0) {

        		log_warn("Warning: Unable to fetch config; using last stored config.");
                }
		if (!main_load_previous_config(config, &http_response)) {
		        string_free(&http_response);
			return -1;
		}
	}

	if (string_equals(&http_response, oldconfig)) {
		string_free(&http_response);
		return 0;
	}

	err = !main_parse_config(config, &http_response);
	if (err) {
		string_free(&http_response);
		return -1;
	}


	main_tempsave_fetched_config(config, &http_response);

	string_free(oldconfig);
	string_move(&http_response, oldconfig);

	log_debug("Backing up old configs.");
	if (!main_create_backup(config)) {
		log_warn("Unable to complete config backup copy from %s to %s.old - ignored.", config->base_path, config->base_path);
	}

	log_debug("Cleanup previous host entries.");
	if (!main_cleanup_hosts_subdir(config)) {
		log_err("Unable to remove previous host subconfigs from %s/hosts/", config->base_path);
		return -1;
	}

	if (!tinc_write_config(config)) return -1;
	if (!tinc_write_hosts(config)) return -1;
	if (!tinc_write_updown(config, true)) return -1;
	if (!tinc_write_updown(config, false)) return -1;
	if (!tinc_write_subnetupdown(config, true)) return -1;
	if (!tinc_write_subnetupdown(config, false)) return -1;

	main_free_parsed_info(config);

	return 1;
}

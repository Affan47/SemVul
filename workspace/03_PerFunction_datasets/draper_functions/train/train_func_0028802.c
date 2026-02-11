load_master_config(const char *card_name, snd_config_t **cfg)
{
	char filename[MAX_FILE];
	char *env = getenv(ALSA_CONFIG_UCM_VAR);
	int err;

	snprintf(filename, sizeof(filename)-1,
		"%s/%s/%s.conf", env ? env : ALSA_USE_CASE_DIR,
		card_name, card_name);
	filename[MAX_FILE-1] = '\0';

	err = uc_mgr_config_load(filename, cfg);
	if (err < 0) {
		uc_error("error: could not parse configuration for card %s",
				card_name);
		return err;
	}

	return 0;
}

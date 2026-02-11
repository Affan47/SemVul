uc_mgr_config_load(const char *file, snd_config_t **cfg)
{
	FILE *fp;
	snd_input_t *in;
	snd_config_t *top;
	int err;

	fp = fopen(file, "r");
	if (fp == NULL) {
		err = -errno;
		goto __err;
	}
	err = snd_input_stdio_attach(&in, fp, 1);
	if (err < 0) {
	      __err:
		uc_error("could not open configuration file %s", file);
		return err;
	}
	err = snd_config_top(&top);
	if (err < 0)
		return err;
	err = snd_config_load(top, in);
	if (err < 0) {
		uc_error("could not load configuration file %s", file);
		snd_config_delete(top);
		return err;
	}
	err = snd_input_close(in);
	if (err < 0) {
		snd_config_delete(top);
		return err;
	}
	*cfg = top;
	return 0;
}

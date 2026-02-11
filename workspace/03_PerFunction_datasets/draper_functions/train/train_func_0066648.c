ndmcfg_loadfp (FILE *fp, ndmp9_config_info *config_info)
{
	struct cfg_cb	_cb, *cb = &_cb;
	int		rc;

	NDMOS_MACRO_ZEROFILL(cb);

	cb->fp = fp;
	cb->config_info = config_info;

	for (;;) {
		rc = ndmstz_getstanza (cb->fp, cb->buf, sizeof cb->buf);
		if (rc == EOF) {
			break;
		}

		cb->sc = ndmstz_parse (cb->buf, cb->sv, CFG_MAX_SV);
		if (cb->sc < 1) {
			continue;
		}

		if (strcmp (cb->sv[0], "butype") == 0 && cb->sc == 2) {
			cfg_butype (cb);
			continue;
		}

		if (strcmp (cb->sv[0], "fs") == 0 && cb->sc == 2) {
			cfg_fs (cb);
			continue;
		}

		if (strcmp (cb->sv[0], "tape") == 0 && cb->sc == 2) {
			cfg_tape (cb);
			continue;
		}

		if (strcmp (cb->sv[0], "scsi") == 0 && cb->sc == 2) {
			cfg_scsi (cb);
			continue;
		}


	}

	return cb->n_error;
}

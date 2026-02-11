wlcore_adjust_conf(struct wl1271 *wl)
{


	if (fwlog_mem_blocks != -1) {
		if (fwlog_mem_blocks >= CONF_FWLOG_MIN_MEM_BLOCKS &&
		    fwlog_mem_blocks <= CONF_FWLOG_MAX_MEM_BLOCKS) {
			wl->conf.fwlog.mem_blocks = fwlog_mem_blocks;
		} else {
			wl1271_error(
				"Illegal fwlog_mem_blocks=%d using default %d",
				fwlog_mem_blocks, wl->conf.fwlog.mem_blocks);
		}
	}

	if (fwlog_param) {
		if (!strcmp(fwlog_param, "continuous")) {
			wl->conf.fwlog.mode = WL12XX_FWLOG_CONTINUOUS;
		} else if (!strcmp(fwlog_param, "ondemand")) {
			wl->conf.fwlog.mode = WL12XX_FWLOG_ON_DEMAND;
		} else if (!strcmp(fwlog_param, "dbgpins")) {
			wl->conf.fwlog.mode = WL12XX_FWLOG_CONTINUOUS;
			wl->conf.fwlog.output = WL12XX_FWLOG_OUTPUT_DBG_PINS;
		} else if (!strcmp(fwlog_param, "disable")) {
			wl->conf.fwlog.mem_blocks = 0;
			wl->conf.fwlog.output = WL12XX_FWLOG_OUTPUT_NONE;
		} else {
			wl1271_error("Unknown fwlog parameter %s", fwlog_param);
		}
	}

	if (bug_on_recovery != -1)
		wl->conf.recovery.bug_on_recovery = (u8) bug_on_recovery;

	if (no_recovery != -1)
		wl->conf.recovery.no_recovery = (u8) no_recovery;
}

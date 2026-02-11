dvb_fe_retrieve_stats(struct dvb_v5_fe_parms *parms,
			  unsigned cmd, uint32_t *value)
{
	struct dtv_stats *stat;
	enum fecap_scale_params scale;

	stat = dvb_fe_retrieve_stats_layer(parms, cmd, 0);
	if (!stat) {
		if (parms->verbose)
			dvb_logdbg("%s not found on retrieve", dvb_cmd_name(cmd));
		return EINVAL;
	}

	scale = stat->scale;
	if (scale == FE_SCALE_NOT_AVAILABLE) {
		if (parms->verbose)
			dvb_logdbg("%s not available", dvb_cmd_name(cmd));
		return EINVAL;
	}

	*value = stat->uvalue;

	if (parms->verbose)
		dvb_logdbg("Stats for %s = %d", dvb_cmd_name(cmd), *value);

	return 0;
}

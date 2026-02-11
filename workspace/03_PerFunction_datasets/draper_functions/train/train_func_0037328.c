dvb_fe_retrieve_parm(const struct dvb_v5_fe_parms *parms,
				unsigned cmd, uint32_t *value)
{
	int i;
	for (i = 0; i < parms->n_props; i++) {
		if (parms->dvb_prop[i].cmd != cmd)
			continue;
		*value = parms->dvb_prop[i].u.data;
		return 0;
	}
	dvb_logerr("command %s (%d) not found during retrieve",
		dvb_cmd_name(cmd), cmd);

	return EINVAL;
}

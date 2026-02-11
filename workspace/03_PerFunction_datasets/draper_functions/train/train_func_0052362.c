cfhsi_can_send_aggregate(struct cfhsi *cfhsi)
{
	int i;

	if (cfhsi->cfg.aggregation_timeout == 0)
		return true;

	for (i = 0; i < CFHSI_PRIO_BEBK; ++i) {
		if (cfhsi->qhead[i].qlen)
			return true;
	}


	if (cfhsi->qhead[CFHSI_PRIO_BEBK].qlen >= CFHSI_MAX_PKTS)
		return true;

	return false;
}

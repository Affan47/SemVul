check_enable(struct bau_control *bcp, struct ptc_stats *stat)
{
	int tcpu;
	struct bau_control *tbcp;
	struct bau_control *hmaster;

	hmaster = bcp->uvhub_master;
	spin_lock(&hmaster->disable_lock);
	if (bcp->baudisabled && (get_cycles() >= bcp->set_bau_on_time)) {
		stat->s_bau_reenabled++;
		for_each_present_cpu(tcpu) {
			tbcp = &per_cpu(bau_control, tcpu);
			if (tbcp->uvhub_master == hmaster) {
				tbcp->baudisabled = 0;
				tbcp->period_requests = 0;
				tbcp->period_time = 0;
				tbcp->period_giveups = 0;
			}
		}
		spin_unlock(&hmaster->disable_lock);
		return 0;
	}
	spin_unlock(&hmaster->disable_lock);
	return -1;
}

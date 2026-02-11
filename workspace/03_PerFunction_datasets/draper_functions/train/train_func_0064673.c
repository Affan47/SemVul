fnic_reset_host_stats(struct Scsi_Host *host)
{
	int ret;
	struct fc_lport *lp = shost_priv(host);
	struct fnic *fnic = lport_priv(lp);
	struct fc_host_statistics *stats;
	unsigned long flags;


	stats = fnic_get_stats(host);
	fnic_dump_fchost_stats(host, stats);

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	ret = vnic_dev_stats_clear(fnic->vdev);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	if (ret) {
		FNIC_MAIN_DBG(KERN_DEBUG, fnic->lport->host,
				"fnic: Reset vnic stats failed"
				" 0x%x", ret);
		return;
	}
	fnic->stats_reset_time = jiffies;
	memset(stats, 0, sizeof(*stats));

	return;
}

scsi_try_bus_reset(struct scsi_cmnd *scmd)
{
	unsigned long flags;
	int rtn;
	struct Scsi_Host *host = scmd->device->host;
	struct scsi_host_template *hostt = host->hostt;

	SCSI_LOG_ERROR_RECOVERY(3, scmd_printk(KERN_INFO, scmd,
		"%s: Snd Bus RST\n", __func__));

	if (!hostt->eh_bus_reset_handler)
		return FAILED;

	rtn = hostt->eh_bus_reset_handler(scmd);

	if (rtn == SUCCESS) {
		if (!hostt->skip_settle_delay)
			ssleep(BUS_RESET_SETTLE_TIME);
		spin_lock_irqsave(host->host_lock, flags);
		scsi_report_bus_reset(host, scmd_channel(scmd));
		spin_unlock_irqrestore(host->host_lock, flags);
	}

	return rtn;
}

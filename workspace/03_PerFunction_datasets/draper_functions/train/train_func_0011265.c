scsih_scan_start(struct Scsi_Host *shost)
{
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	int rc;
	if (diag_buffer_enable != -1 && diag_buffer_enable != 0)
		mpt3sas_enable_diag_buffer(ioc, diag_buffer_enable);

	if (disable_discovery > 0)
		return;

	ioc->start_scan = 1;
	rc = mpt3sas_port_enable(ioc);

	if (rc != 0)
		pr_info(MPT3SAS_FMT "port enable: FAILED\n", ioc->name);
}

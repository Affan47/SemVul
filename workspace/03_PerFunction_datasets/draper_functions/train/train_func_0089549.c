artop6210_qc_defer(struct ata_queued_cmd *qc)
{
	struct ata_host *host = qc->ap->host;
	struct ata_port *alt = host->ports[1 ^ qc->ap->port_no];
	int rc;


	rc = ata_std_qc_defer(qc);
	if (rc != 0)
		return rc;


	if (alt && alt->qc_active)
		return	ATA_DEFER_PORT;
	return 0;
}

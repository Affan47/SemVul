ahci_vt8251_hardreset(struct ata_link *link, unsigned int *class,
				 unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ahci_host_priv *hpriv = ap->host->private_data;
	bool online;
	int rc;

	DPRINTK("ENTER\n");

	ahci_stop_engine(ap);

	rc = sata_link_hardreset(link, sata_ehc_deb_timing(&link->eh_context),
				 deadline, &online, NULL);

	hpriv->start_engine(ap);

	DPRINTK("EXIT, rc=%d, class=%u\n", rc, *class);


	return online ? -EAGAIN : rc;
}

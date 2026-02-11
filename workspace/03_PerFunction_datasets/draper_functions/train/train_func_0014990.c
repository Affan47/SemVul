ahci_host_activate_multi_irqs(struct ata_host *host, int irq,
					 struct scsi_host_template *sht)
{
	int i, rc;

	rc = ata_host_start(host);
	if (rc)
		return rc;


	for (i = 0; i < host->n_ports; i++) {
		struct ahci_port_priv *pp = host->ports[i]->private_data;


		if (!pp) {
			disable_irq(irq + i);
			continue;
		}

		rc = devm_request_threaded_irq(host->dev, irq + i,
					       ahci_multi_irqs_intr,
					       ahci_port_thread_fn, 0,
					       pp->irq_desc, host->ports[i]);
		if (rc)
			return rc;
		ata_port_desc(host->ports[i], "irq %d", irq + i);
	}
	return ata_host_register(host, sht);
}

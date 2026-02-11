ahci_gtf_filter_workaround(struct ata_host *host)
{
	static const struct dmi_system_id sysids[] = {


		{
			.ident = "Aspire 3810T",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 3810T"),
			},
			.driver_data = (void *)ATA_ACPI_FILTER_FPDMA_OFFSET,
		},
		{ }
	};
	const struct dmi_system_id *dmi = dmi_first_match(sysids);
	unsigned int filter;
	int i;

	if (!dmi)
		return;

	filter = (unsigned long)dmi->driver_data;
	dev_info(host->dev, "applying extra ACPI _GTF filter 0x%x for %s\n",
		 filter, dmi->ident);

	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];
		struct ata_link *link;
		struct ata_device *dev;

		ata_for_each_link(link, ap, EDGE)
			ata_for_each_dev(dev, link, ALL)
				dev->gtf_filter |= filter;
	}
}

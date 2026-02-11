ipr_check_term_power(struct ipr_ioa_cfg *ioa_cfg,
				 struct ipr_mode_pages *mode_pages)
{
	int i;
	int entry_length;
	struct ipr_dev_bus_entry *bus;
	struct ipr_mode_page28 *mode_page;

	mode_page = ipr_get_mode_page(mode_pages, 0x28,
				      sizeof(struct ipr_mode_page28));

	entry_length = mode_page->entry_length;

	bus = mode_page->bus;

	for (i = 0; i < mode_page->num_entries; i++) {
		if (bus->flags & IPR_SCSI_ATTR_NO_TERM_PWR) {
			dev_err(&ioa_cfg->pdev->dev,
				"Term power is absent on scsi bus %d\n",
				bus->res_addr.bus);
		}

		bus = (struct ipr_dev_bus_entry *)((char *)bus + entry_length);
	}
}

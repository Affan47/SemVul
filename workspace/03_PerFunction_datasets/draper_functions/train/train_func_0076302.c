sata_pmp_same_pmp(struct ata_device *dev, const u32 *new_gscr)
{
	const u32 *old_gscr = dev->gscr;
	u16 old_vendor, new_vendor, old_devid, new_devid;
	int old_nr_ports, new_nr_ports;

	old_vendor = sata_pmp_gscr_vendor(old_gscr);
	new_vendor = sata_pmp_gscr_vendor(new_gscr);
	old_devid = sata_pmp_gscr_devid(old_gscr);
	new_devid = sata_pmp_gscr_devid(new_gscr);
	old_nr_ports = sata_pmp_gscr_ports(old_gscr);
	new_nr_ports = sata_pmp_gscr_ports(new_gscr);

	if (old_vendor != new_vendor) {
		ata_dev_info(dev,
			     "Port Multiplier vendor mismatch '0x%x' != '0x%x'\n",
			     old_vendor, new_vendor);
		return 0;
	}

	if (old_devid != new_devid) {
		ata_dev_info(dev,
			     "Port Multiplier device ID mismatch '0x%x' != '0x%x'\n",
			     old_devid, new_devid);
		return 0;
	}

	if (old_nr_ports != new_nr_ports) {
		ata_dev_info(dev,
			     "Port Multiplier nr_ports mismatch '0x%x' != '0x%x'\n",
			     old_nr_ports, new_nr_ports);
		return 0;
	}

	return 1;
}

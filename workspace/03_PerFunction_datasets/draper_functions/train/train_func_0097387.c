mp_find_ioapic(u32 gsi)
{
	int i;

	if (nr_ioapics == 0)
		return -1;


	for_each_ioapic(i) {
		struct mp_ioapic_gsi *gsi_cfg = mp_ioapic_gsi_routing(i);
		if (gsi >= gsi_cfg->gsi_base && gsi <= gsi_cfg->gsi_end)
			return i;
	}

	printk(KERN_ERR "ERROR: Unable to locate IOAPIC for GSI %d\n", gsi);
	return -1;
}

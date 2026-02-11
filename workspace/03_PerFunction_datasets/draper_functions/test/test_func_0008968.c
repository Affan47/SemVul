ioapic_insert_resources(void)
{
	int i;
	struct resource *r = ioapic_resources;

	if (!r) {
		if (nr_ioapics > 0)
			printk(KERN_ERR
				"IO APIC resources couldn't be allocated.\n");
		return;
	}

	for_each_ioapic(i) {
		insert_resource(&iomem_resource, r);
		r++;
	}
}

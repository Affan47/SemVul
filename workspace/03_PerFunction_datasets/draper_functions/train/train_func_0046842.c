pci_fail_res_type_mask(struct list_head *fail_head)
{
	struct pci_dev_resource *fail_res;
	unsigned long mask = 0;


	list_for_each_entry(fail_res, fail_head, list)
		mask |= fail_res->flags;


	return mask & (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PREFETCH);
}

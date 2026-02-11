assign_fixed_resource_on_bus(struct pci_bus *b, struct resource *r)
{
	int i;
	struct resource *parent_r;
	unsigned long mask = IORESOURCE_IO | IORESOURCE_MEM |
			     IORESOURCE_PREFETCH;

	pci_bus_for_each_resource(b, parent_r, i) {
		if (!parent_r)
			continue;

		if ((r->flags & mask) == (parent_r->flags & mask) &&
		    resource_contains(parent_r, r))
			request_resource(parent_r, r);
	}
}

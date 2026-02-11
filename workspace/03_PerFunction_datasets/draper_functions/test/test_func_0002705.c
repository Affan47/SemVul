pnpacpi_add_irqresource(struct pnp_dev *dev, struct resource *r)
{
	if (!(r->flags & IORESOURCE_DISABLED))
		pcibios_penalize_isa_irq(r->start, 1);

	pnp_add_resource(dev, r);
}

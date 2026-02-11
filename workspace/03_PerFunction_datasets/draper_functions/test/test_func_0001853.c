pnp_register_irq_resource(struct pnp_dev *dev, unsigned int option_flags,
			      pnp_irq_mask_t *map, unsigned char flags)
{
	struct pnp_option *option;
	struct pnp_irq *irq;

	option = pnp_build_option(dev, IORESOURCE_IRQ, option_flags);
	if (!option)
		return -ENOMEM;

	irq = &option->u.irq;
	irq->map = *map;
	irq->flags = flags;

#ifdef CONFIG_PCI
	{
		int i;

		for (i = 0; i < 16; i++)
			if (test_bit(i, irq->map.bits))
				pcibios_penalize_isa_irq(i, 0);
	}
#endif

	dbg_pnp_show_option(dev, option);
	return 0;
}

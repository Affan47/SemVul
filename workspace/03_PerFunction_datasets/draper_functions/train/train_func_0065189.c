pnp_possible_config(struct pnp_dev *dev, int type, resource_size_t start,
			resource_size_t size)
{
	struct pnp_option *option;
	struct pnp_port *port;
	struct pnp_mem *mem;
	struct pnp_irq *irq;
	struct pnp_dma *dma;

	list_for_each_entry(option, &dev->options, list) {
		if (option->type != type)
			continue;

		switch (option->type) {
		case IORESOURCE_IO:
			port = &option->u.port;
			if (port->min == start && port->size == size)
				return 1;
			break;
		case IORESOURCE_MEM:
			mem = &option->u.mem;
			if (mem->min == start && mem->size == size)
				return 1;
			break;
		case IORESOURCE_IRQ:
			irq = &option->u.irq;
			if (start < PNP_IRQ_NR &&
			    test_bit(start, irq->map.bits))
				return 1;
			break;
		case IORESOURCE_DMA:
			dma = &option->u.dma;
			if (dma->map & (1 << start))
				return 1;
			break;
		}
	}

	return 0;
}

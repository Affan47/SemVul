pnp_check_dma(struct pnp_dev *dev, struct resource *res)
{
	int i;
	struct pnp_dev *tdev;
	struct resource *tres;
	resource_size_t *dma;

	dma = &res->start;


	if (cannot_compare(res->flags))
		return 1;


	if (*dma == 4 || *dma > 7)
		return 0;


	for (i = 0; i < 8; i++) {
		if (pnp_reserve_dma[i] == *dma)
			return 0;
	}


	for (i = 0; (tres = pnp_get_resource(dev, IORESOURCE_DMA, i)); i++) {
		if (tres != res && tres->flags & IORESOURCE_DMA) {
			if (tres->start == *dma)
				return 0;
		}
	}


	if (!dev->active) {
		if (request_dma(*dma, "pnp"))
			return 0;
		free_dma(*dma);
	}


	pnp_for_each_dev(tdev) {
		if (tdev == dev)
			continue;
		for (i = 0;
		     (tres = pnp_get_resource(tdev, IORESOURCE_DMA, i));
		     i++) {
			if (tres->flags & IORESOURCE_DMA) {
				if (cannot_compare(tres->flags))
					continue;
				if (tres->start == *dma)
					return 0;
			}
		}
	}

	return 1;
}

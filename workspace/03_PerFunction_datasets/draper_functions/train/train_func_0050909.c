pnp_add_bus_resource(struct pnp_dev *dev,
					  resource_size_t start,
					  resource_size_t end)
{
	struct pnp_resource *pnp_res;
	struct resource *res;

	pnp_res = pnp_new_resource(dev);
	if (!pnp_res) {
		dev_err(&dev->dev, "can't add resource for BUS %#llx-%#llx\n",
			(unsigned long long) start,
			(unsigned long long) end);
		return NULL;
	}

	res = &pnp_res->res;
	res->flags = IORESOURCE_BUS;
	res->start = start;
	res->end = end;

	dev_printk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	return pnp_res;
}

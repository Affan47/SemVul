rcar_dmac_parse_of(struct device *dev, struct rcar_dmac *dmac)
{
	struct device_node *np = dev->of_node;
	int ret;

	ret = of_property_read_u32(np, "dma-channels", &dmac->n_channels);
	if (ret < 0) {
		dev_err(dev, "unable to read dma-channels property\n");
		return ret;
	}

	if (dmac->n_channels <= 0 || dmac->n_channels >= 100) {
		dev_err(dev, "invalid number of channels %u\n",
			dmac->n_channels);
		return -EINVAL;
	}

	return 0;
}

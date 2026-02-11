wlcore_probe_of(struct device *dev, int *irq,
			   struct wlcore_platdev_data *pdev_data)
{
	struct device_node *np = dev->of_node;

	if (!np || !of_match_node(wlcore_sdio_of_match_table, np))
		return -ENODATA;

	*irq = irq_of_parse_and_map(np, 0);
	if (!*irq) {
		dev_err(dev, "No irq in platform data\n");
		kfree(pdev_data);
		return -EINVAL;
	}


	of_property_read_u32(np, "ref-clock-frequency",
			     &pdev_data->ref_clock_freq);
	of_property_read_u32(np, "tcxo-clock-frequency",
			     &pdev_data->tcxo_clock_freq);

	return 0;
}

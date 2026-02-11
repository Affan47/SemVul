dwapb_gpio_get_pdata_of(struct device *dev)
{
	struct device_node *node, *port_np;
	struct dwapb_platform_data *pdata;
	struct dwapb_port_property *pp;
	int nports;
	int i;

	node = dev->of_node;
	if (!IS_ENABLED(CONFIG_OF_GPIO) || !node)
		return ERR_PTR(-ENODEV);

	nports = of_get_child_count(node);
	if (nports == 0)
		return ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return ERR_PTR(-ENOMEM);

	pdata->properties = devm_kcalloc(dev, nports, sizeof(*pp), GFP_KERNEL);
	if (!pdata->properties)
		return ERR_PTR(-ENOMEM);

	pdata->nports = nports;

	i = 0;
	for_each_child_of_node(node, port_np) {
		pp = &pdata->properties[i++];
		pp->node = port_np;

		if (of_property_read_u32(port_np, "reg", &pp->idx) ||
		    pp->idx >= DWAPB_MAX_PORTS) {
			dev_err(dev, "missing/invalid port index for %s\n",
				port_np->full_name);
			return ERR_PTR(-EINVAL);
		}

		if (of_property_read_u32(port_np, "snps,nr-gpios",
					 &pp->ngpio)) {
			dev_info(dev, "failed to get number of gpios for %s\n",
				 port_np->full_name);
			pp->ngpio = 32;
		}


		if (pp->idx == 0 &&
		    of_property_read_bool(port_np, "interrupt-controller")) {
			pp->irq = irq_of_parse_and_map(port_np, 0);
			if (!pp->irq) {
				dev_warn(dev, "no irq for bank %s\n",
					 port_np->full_name);
			}
		}

		pp->irq_shared	= false;
		pp->gpio_base	= -1;
		pp->name	= port_np->full_name;
	}

	return pdata;
}

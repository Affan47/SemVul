pnp_assign_resources(struct pnp_dev *dev, int set)
{
	struct pnp_option *option;
	int nport = 0, nmem = 0, nirq = 0;
	int ndma __maybe_unused = 0;
	int ret = 0;

	pnp_dbg(&dev->dev, "pnp_assign_resources, try dependent set %d\n", set);
	mutex_lock(&pnp_res_mutex);
	pnp_clean_resource_table(dev);

	list_for_each_entry(option, &dev->options, list) {
		if (pnp_option_is_dependent(option) &&
		    pnp_option_set(option) != set)
				continue;

		switch (option->type) {
		case IORESOURCE_IO:
			ret = pnp_assign_port(dev, &option->u.port, nport++);
			break;
		case IORESOURCE_MEM:
			ret = pnp_assign_mem(dev, &option->u.mem, nmem++);
			break;
		case IORESOURCE_IRQ:
			ret = pnp_assign_irq(dev, &option->u.irq, nirq++);
			break;
#ifdef CONFIG_ISA_DMA_API
		case IORESOURCE_DMA:
			ret = pnp_assign_dma(dev, &option->u.dma, ndma++);
			break;
#endif
		default:
			ret = -EINVAL;
			break;
		}
		if (ret < 0)
			break;
	}

	mutex_unlock(&pnp_res_mutex);
	if (ret < 0) {
		pnp_dbg(&dev->dev, "pnp_assign_resources failed (%d)\n", ret);
		pnp_clean_resource_table(dev);
	} else
		dbg_pnp_show_resources(dev, "pnp_assign_resources succeeded");
	return ret;
}

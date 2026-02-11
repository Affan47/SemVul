mfd_add_devices(struct device *parent, int id,
		    const struct mfd_cell *cells, int n_devs,
		    struct resource *mem_base,
		    int irq_base, struct irq_domain *domain)
{
	int i;
	int ret;
	atomic_t *cnts;


	cnts = kcalloc(n_devs, sizeof(*cnts), GFP_KERNEL);
	if (!cnts)
		return -ENOMEM;

	for (i = 0; i < n_devs; i++) {
		atomic_set(&cnts[i], 0);
		ret = mfd_add_device(parent, id, cells + i, cnts + i, mem_base,
				     irq_base, domain);
		if (ret)
			goto fail;
	}

	return 0;

fail:
	if (i)
		mfd_remove_devices(parent);
	else
		kfree(cnts);
	return ret;
}

fam15h_power_init_attrs(struct pci_dev *pdev,
				   struct fam15h_power_data *data)
{
	int n = FAM15H_MIN_NUM_ATTRS;
	struct attribute **fam15h_power_attrs;
	struct cpuinfo_x86 *c = &boot_cpu_data;

	if (c->x86 == 0x15 &&
	    (c->x86_model <= 0xf ||
	     (c->x86_model >= 0x60 && c->x86_model <= 0x6f)))
		n += 1;

	fam15h_power_attrs = devm_kcalloc(&pdev->dev, n,
					  sizeof(*fam15h_power_attrs),
					  GFP_KERNEL);

	if (!fam15h_power_attrs)
		return -ENOMEM;

	n = 0;
	fam15h_power_attrs[n++] = &dev_attr_power1_crit.attr;
	if (c->x86 == 0x15 &&
	    (c->x86_model <= 0xf ||
	     (c->x86_model >= 0x60 && c->x86_model <= 0x6f)))
		fam15h_power_attrs[n++] = &dev_attr_power1_input.attr;

	data->group.attrs = fam15h_power_attrs;

	return 0;
}

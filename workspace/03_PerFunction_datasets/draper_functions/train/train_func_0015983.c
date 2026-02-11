dwc2_debugfs_init(struct dwc2_hsotg *hsotg)
{
	int			ret;
	struct dentry		*file;

	hsotg->debug_root = debugfs_create_dir(dev_name(hsotg->dev), NULL);
	if (!hsotg->debug_root) {
		ret = -ENOMEM;
		goto err0;
	}


	dwc2_hsotg_create_debug(hsotg);

	hsotg->regset = devm_kzalloc(hsotg->dev, sizeof(*hsotg->regset),
								GFP_KERNEL);
	if (!hsotg->regset) {
		ret = -ENOMEM;
		goto err1;
	}

	hsotg->regset->regs = dwc2_regs;
	hsotg->regset->nregs = ARRAY_SIZE(dwc2_regs);
	hsotg->regset->base = hsotg->regs;

	file = debugfs_create_regset32("regdump", S_IRUGO, hsotg->debug_root,
								hsotg->regset);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	return 0;
err1:
	debugfs_remove_recursive(hsotg->debug_root);
err0:
	return ret;
}

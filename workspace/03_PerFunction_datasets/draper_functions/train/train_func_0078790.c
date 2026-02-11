nvm_init(struct nvm_dev *dev)
{
	int ret = -EINVAL;

	if (!dev->q || !dev->ops)
		return ret;

	if (dev->ops->identity(dev, &dev->identity)) {
		pr_err("nvm: device could not be identified\n");
		goto err;
	}

	pr_debug("nvm: ver:%x nvm_vendor:%x groups:%u\n",
			dev->identity.ver_id, dev->identity.vmnt,
							dev->identity.cgrps);

	if (dev->identity.ver_id != 1) {
		pr_err("nvm: device not supported by kernel.");
		goto err;
	}

	if (dev->identity.cgrps != 1) {
		pr_err("nvm: only one group configuration supported.");
		goto err;
	}

	ret = nvm_core_init(dev);
	if (ret) {
		pr_err("nvm: could not initialize core structures.\n");
		goto err;
	}

	pr_info("nvm: registered %s [%u/%u/%u/%u/%u/%u]\n",
			dev->name, dev->sec_per_pg, dev->nr_planes,
			dev->pgs_per_blk, dev->blks_per_lun, dev->nr_luns,
			dev->nr_chnls);
	return 0;
err:
	pr_err("nvm: failed to initialize nvm\n");
	return ret;
}

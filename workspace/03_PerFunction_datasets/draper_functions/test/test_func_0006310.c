dwc2_hsotg_create_debug(struct dwc2_hsotg *hsotg)
{
	struct dentry *root;
	struct dentry *file;
	unsigned epidx;

	root = hsotg->debug_root;


	file = debugfs_create_file("state", S_IRUGO, root, hsotg, &state_fops);
	if (IS_ERR(file))
		dev_err(hsotg->dev, "%s: failed to create state\n", __func__);

	file = debugfs_create_file("testmode", S_IRUGO | S_IWUSR, root, hsotg,
							&testmode_fops);
	if (IS_ERR(file))
		dev_err(hsotg->dev, "%s: failed to create testmode\n",
				__func__);

	file = debugfs_create_file("fifo", S_IRUGO, root, hsotg, &fifo_fops);
	if (IS_ERR(file))
		dev_err(hsotg->dev, "%s: failed to create fifo\n", __func__);


	for (epidx = 0; epidx < hsotg->num_of_eps; epidx++) {
		struct dwc2_hsotg_ep *ep;

		ep = hsotg->eps_out[epidx];
		if (ep) {
			file = debugfs_create_file(ep->name, S_IRUGO,
							  root, ep, &ep_fops);
			if (IS_ERR(file))
				dev_err(hsotg->dev, "failed to create %s debug file\n",
					ep->name);
		}
	}

	for (epidx = 1; epidx < hsotg->num_of_eps; epidx++) {
		struct dwc2_hsotg_ep *ep;

		ep = hsotg->eps_in[epidx];
		if (ep) {
			file = debugfs_create_file(ep->name, S_IRUGO,
							  root, ep, &ep_fops);
			if (IS_ERR(file))
				dev_err(hsotg->dev, "failed to create %s debug file\n",
					ep->name);
		}
	}
}

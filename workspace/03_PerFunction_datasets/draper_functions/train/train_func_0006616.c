dwc2_hsotg_hw_cfg(struct dwc2_hsotg *hsotg)
{
	u32 cfg;
	u32 ep_type;
	u32 i;


	cfg = dwc2_readl(hsotg->regs + GHWCFG2);
	hsotg->num_of_eps = (cfg >> GHWCFG2_NUM_DEV_EP_SHIFT) & 0xF;

	hsotg->num_of_eps++;

	hsotg->eps_in[0] = devm_kzalloc(hsotg->dev, sizeof(struct dwc2_hsotg_ep),
								GFP_KERNEL);
	if (!hsotg->eps_in[0])
		return -ENOMEM;

	hsotg->eps_out[0] = hsotg->eps_in[0];

	cfg = dwc2_readl(hsotg->regs + GHWCFG1);
	for (i = 1, cfg >>= 2; i < hsotg->num_of_eps; i++, cfg >>= 2) {
		ep_type = cfg & 3;

		if (!(ep_type & 2)) {
			hsotg->eps_in[i] = devm_kzalloc(hsotg->dev,
				sizeof(struct dwc2_hsotg_ep), GFP_KERNEL);
			if (!hsotg->eps_in[i])
				return -ENOMEM;
		}

		if (!(ep_type & 1)) {
			hsotg->eps_out[i] = devm_kzalloc(hsotg->dev,
				sizeof(struct dwc2_hsotg_ep), GFP_KERNEL);
			if (!hsotg->eps_out[i])
				return -ENOMEM;
		}
	}

	cfg = dwc2_readl(hsotg->regs + GHWCFG3);
	hsotg->fifo_mem = (cfg >> GHWCFG3_DFIFO_DEPTH_SHIFT);

	cfg = dwc2_readl(hsotg->regs + GHWCFG4);
	hsotg->dedicated_fifos = (cfg >> GHWCFG4_DED_FIFO_SHIFT) & 1;

	dev_info(hsotg->dev, "EPs: %d, %s fifos, %d entries in SPRAM\n",
		 hsotg->num_of_eps,
		 hsotg->dedicated_fifos ? "dedicated" : "shared",
		 hsotg->fifo_mem);
	return 0;
}

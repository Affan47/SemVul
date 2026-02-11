skl_sst_dsp_init(struct device *dev, void __iomem *mmio_base, int irq,
		struct skl_dsp_loader_ops dsp_ops, struct skl_sst **dsp)
{
	struct skl_sst *skl;
	struct sst_dsp *sst;
	int ret;

	skl = devm_kzalloc(dev, sizeof(*skl), GFP_KERNEL);
	if (skl == NULL)
		return -ENOMEM;

	skl->dev = dev;
	skl_dev.thread_context = skl;

	skl->dsp = skl_dsp_ctx_init(dev, &skl_dev, irq);
	if (!skl->dsp) {
		dev_err(skl->dev, "%s: no device\n", __func__);
		return -ENODEV;
	}

	sst = skl->dsp;

	sst->addr.lpe = mmio_base;
	sst->addr.shim = mmio_base;
	sst_dsp_mailbox_init(sst, (SKL_ADSP_SRAM0_BASE + SKL_ADSP_W0_STAT_SZ),
			SKL_ADSP_W0_UP_SZ, SKL_ADSP_SRAM1_BASE, SKL_ADSP_W1_SZ);

	sst->dsp_ops = dsp_ops;
	sst->fw_ops = skl_fw_ops;

	ret = skl_ipc_init(dev, skl);
	if (ret)
		return ret;

	ret = sst->fw_ops.load_fw(sst);
	if (ret < 0) {
		dev_err(dev, "Load base fw failed : %d", ret);
		return ret;
	}

	if (dsp)
		*dsp = skl;

	return 0;

	skl_ipc_free(&skl->ipc);
	return ret;
}

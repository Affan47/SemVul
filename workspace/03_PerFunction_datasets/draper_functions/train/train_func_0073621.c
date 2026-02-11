vc4_hvs_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = drm->dev_private;
	struct vc4_hvs *hvs = NULL;

	hvs = devm_kzalloc(&pdev->dev, sizeof(*hvs), GFP_KERNEL);
	if (!hvs)
		return -ENOMEM;

	hvs->pdev = pdev;

	hvs->regs = vc4_ioremap_regs(pdev, 0);
	if (IS_ERR(hvs->regs))
		return PTR_ERR(hvs->regs);

	hvs->dlist = hvs->regs + SCALER_DLIST_START;

	vc4->hvs = hvs;
	return 0;
}

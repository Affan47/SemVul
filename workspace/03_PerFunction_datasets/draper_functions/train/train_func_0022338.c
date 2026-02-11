lp8788_backlight_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	struct lp8788_bl *bl;
	int ret;

	bl = devm_kzalloc(lp->dev, sizeof(struct lp8788_bl), GFP_KERNEL);
	if (!bl)
		return -ENOMEM;

	bl->lp = lp;
	if (lp->pdata)
		bl->pdata = lp->pdata->bl_pdata;

	platform_set_drvdata(pdev, bl);

	ret = lp8788_backlight_configure(bl);
	if (ret) {
		dev_err(lp->dev, "backlight config err: %d\n", ret);
		goto err_dev;
	}

	ret = lp8788_backlight_register(bl);
	if (ret) {
		dev_err(lp->dev, "register backlight err: %d\n", ret);
		goto err_dev;
	}

	ret = sysfs_create_group(&pdev->dev.kobj, &lp8788_attr_group);
	if (ret) {
		dev_err(lp->dev, "register sysfs err: %d\n", ret);
		goto err_sysfs;
	}

	backlight_update_status(bl->bl_dev);

	return 0;

err_sysfs:
	lp8788_backlight_unregister(bl);
err_dev:
	return ret;
}

w1_ds2760_add_slave(struct w1_slave *sl)
{
	int ret;
	int id;
	struct platform_device *pdev;

	id = ida_simple_get(&bat_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		ret = id;
		goto noid;
	}

	pdev = platform_device_alloc("ds2760-battery", id);
	if (!pdev) {
		ret = -ENOMEM;
		goto pdev_alloc_failed;
	}
	pdev->dev.parent = &sl->dev;

	ret = platform_device_add(pdev);
	if (ret)
		goto pdev_add_failed;

	dev_set_drvdata(&sl->dev, pdev);

	goto success;

pdev_add_failed:
	platform_device_put(pdev);
pdev_alloc_failed:
	ida_simple_remove(&bat_ida, id);
noid:
success:
	return ret;
}

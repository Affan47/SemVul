hid_sensor_setup_trigger(struct iio_dev *indio_dev, const char *name,
				struct hid_sensor_common *attrb)
{
	int ret;
	struct iio_trigger *trig;

	trig = iio_trigger_alloc("%s-dev%d", name, indio_dev->id);
	if (trig == NULL) {
		dev_err(&indio_dev->dev, "Trigger Allocate Failed\n");
		ret = -ENOMEM;
		goto error_ret;
	}

	trig->dev.parent = indio_dev->dev.parent;
	iio_trigger_set_drvdata(trig, attrb);
	trig->ops = &hid_sensor_trigger_ops;
	ret = iio_trigger_register(trig);

	if (ret) {
		dev_err(&indio_dev->dev, "Trigger Register Failed\n");
		goto error_free_trig;
	}
	attrb->trigger = trig;
	indio_dev->trig = iio_trigger_get(trig);

	ret = pm_runtime_set_active(&indio_dev->dev);
	if (ret)
		goto error_unreg_trigger;

	iio_device_set_drvdata(indio_dev, attrb);
	pm_suspend_ignore_children(&attrb->pdev->dev, true);
	pm_runtime_enable(&attrb->pdev->dev);

	pm_runtime_set_autosuspend_delay(&attrb->pdev->dev,
					 3000);
	return ret;
error_unreg_trigger:
	iio_trigger_unregister(trig);
error_free_trig:
	iio_trigger_free(trig);
error_ret:
	return ret;
}

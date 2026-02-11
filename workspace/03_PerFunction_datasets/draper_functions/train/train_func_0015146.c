adxl34x_remove(struct adxl34x *ac)
{
	sysfs_remove_group(&ac->dev->kobj, &adxl34x_attr_group);
	free_irq(ac->irq, ac);
	input_unregister_device(ac->input);
	dev_dbg(ac->dev, "unregistered accelerometer\n");
	kfree(ac);

	return 0;
}

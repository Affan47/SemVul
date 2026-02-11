int3403_cdev_add(struct int3403_priv *priv)
{
	int result = 0;
	acpi_status status;
	struct int3403_cdev *obj;
	struct acpi_buffer buf = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *p;

	obj = devm_kzalloc(&priv->pdev->dev, sizeof(*obj), GFP_KERNEL);
	if (!obj)
		return -ENOMEM;

	status = acpi_evaluate_object(priv->adev->handle, "PPSS", NULL, &buf);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	p = buf.pointer;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		printk(KERN_WARNING "Invalid PPSS data\n");
		kfree(buf.pointer);
		return -EFAULT;
	}

	obj->max_state = p->package.count - 1;
	obj->cdev =
		thermal_cooling_device_register(acpi_device_bid(priv->adev),
				priv, &int3403_cooling_ops);
	if (IS_ERR(obj->cdev))
		result = PTR_ERR(obj->cdev);

	priv->priv = obj;

	kfree(buf.pointer);


	return result;
}

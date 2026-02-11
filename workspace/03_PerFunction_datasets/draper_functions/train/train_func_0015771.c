acpi_nfit_notify(struct acpi_device *adev, u32 event)
{
	struct acpi_nfit_desc *acpi_desc = dev_get_drvdata(&adev->dev);
	struct acpi_buffer buf = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_nfit_header *nfit_saved;
	union acpi_object *obj;
	struct device *dev = &adev->dev;
	acpi_status status;
	int ret;

	dev_dbg(dev, "%s: event: %d\n", __func__, event);

	if (event != NFIT_NOTIFY_UPDATE)
		return;

	device_lock(dev);
	if (!dev->driver) {

		dev_dbg(dev, "%s: no driver found for dev\n", __func__);
		goto out_unlock;
	}

	if (!acpi_desc) {
		acpi_desc = acpi_nfit_desc_init(adev);
		if (IS_ERR(acpi_desc)) {
			dev_err(dev, "%s: error initializing acpi_desc: %ld\n",
				__func__, PTR_ERR(acpi_desc));
			goto out_unlock;
		}
	}


	status = acpi_evaluate_object(adev->handle, "_FIT", NULL, &buf);
	if (ACPI_FAILURE(status)) {
		dev_err(dev, "failed to evaluate _FIT\n");
		goto out_unlock;
	}

	nfit_saved = acpi_desc->nfit;
	obj = buf.pointer;
	if (obj->type == ACPI_TYPE_BUFFER) {
		acpi_desc->nfit =
			(struct acpi_nfit_header *)obj->buffer.pointer;
		ret = acpi_nfit_init(acpi_desc, obj->buffer.length);
		if (ret) {

			acpi_desc->nfit = nfit_saved;
			dev_err(dev, "failed to merge updated NFIT\n");
		}
	} else {

		dev_err(dev, "Invalid _FIT\n");
	}
	kfree(buf.pointer);

 out_unlock:
	device_unlock(dev);
}

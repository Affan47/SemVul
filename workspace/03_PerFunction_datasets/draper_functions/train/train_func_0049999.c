notify_handler(acpi_handle handle, u32 event, void *context)
{
	struct platform_device *device = context;
	struct intel_vbtn_priv *priv = dev_get_drvdata(&device->dev);

	if (!sparse_keymap_report_event(priv->input_dev, event, 1, true))
		dev_info(&device->dev, "unknown event index 0x%x\n",
			 event);
}

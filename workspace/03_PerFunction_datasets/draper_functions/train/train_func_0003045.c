ideapad_acpi_remove(struct platform_device *pdev)
{
	struct ideapad_private *priv = dev_get_drvdata(&pdev->dev);
	int i;

#if IS_ENABLED(CONFIG_ACPI_WMI)
	wmi_remove_notify_handler(ideapad_wmi_fnesc_event);
#endif
	acpi_remove_notify_handler(priv->adev->handle,
		ACPI_DEVICE_NOTIFY, ideapad_acpi_notify);
	ideapad_backlight_exit(priv);
	for (i = 0; i < IDEAPAD_RFKILL_DEV_NUM; i++)
		ideapad_unregister_rfkill(priv, i);
	ideapad_input_exit(priv);
	ideapad_debugfs_exit(priv);
	ideapad_sysfs_exit(priv);
	dev_set_drvdata(&pdev->dev, NULL);

	return 0;
}

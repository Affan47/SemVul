ibm_acpiphp_exit(void)
{
	acpi_status status;
	struct kobject *sysdir = &pci_slots_kset->kobj;

	pr_debug("%s\n", __func__);

	if (acpiphp_unregister_attention(&ibm_attention_info))
		pr_err("%s: attention info deregistration failed", __func__);

	status = acpi_remove_notify_handler(
			   ibm_acpi_handle,
			   ACPI_DEVICE_NOTIFY,
			   ibm_handle_events);
	if (ACPI_FAILURE(status))
		pr_err("%s: Notification handler removal failed\n", __func__);

	sysfs_remove_bin_file(sysdir, &ibm_apci_table_attr);
}

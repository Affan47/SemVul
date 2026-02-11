ata_acpi_uevent(struct ata_port *ap, struct ata_device *dev,
	u32 event)
{
	struct kobject *kobj = NULL;
	char event_string[20];
	char *envp[] = { event_string, NULL };

	if (dev) {
		if (dev->sdev)
			kobj = &dev->sdev->sdev_gendev.kobj;
	} else
		kobj = &ap->dev->kobj;

	if (kobj) {
		snprintf(event_string, 20, "BAY_EVENT=%d", event);
		kobject_uevent_env(kobj, KOBJ_CHANGE, envp);
	}
}

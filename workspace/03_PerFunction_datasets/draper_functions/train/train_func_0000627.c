ata_scsi_hotplug(struct work_struct *work)
{
	struct ata_port *ap =
		container_of(work, struct ata_port, hotplug_task.work);
	int i;

	if (ap->pflags & ATA_PFLAG_UNLOADING) {
		DPRINTK("ENTER/EXIT - unloading\n");
		return;
	}


#ifdef CONFIG_FREEZER
	while (pm_freezing)
		msleep(10);
#endif

	DPRINTK("ENTER\n");
	mutex_lock(&ap->scsi_scan_mutex);


	ata_scsi_handle_link_detach(&ap->link);
	if (ap->pmp_link)
		for (i = 0; i < SATA_PMP_MAX_PORTS; i++)
			ata_scsi_handle_link_detach(&ap->pmp_link[i]);


	ata_scsi_scan_host(ap, 0);

	mutex_unlock(&ap->scsi_scan_mutex);
	DPRINTK("EXIT\n");
}

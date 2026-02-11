lpfc_free_sysfs_attr(struct lpfc_vport *vport)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	sysfs_remove_bin_file(&shost->shost_dev.kobj,
		&sysfs_drvr_stat_data_attr);

	if (vport->port_type == LPFC_NPIV_PORT)
		return;
	sysfs_remove_bin_file(&shost->shost_dev.kobj, &sysfs_mbox_attr);
	sysfs_remove_bin_file(&shost->shost_dev.kobj, &sysfs_ctlreg_attr);
}

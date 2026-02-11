sas_slave_configure(struct scsi_device *scsi_dev)
{
	struct domain_device *dev = sdev_to_domain_dev(scsi_dev);
	struct sas_ha_struct *sas_ha;

	BUG_ON(dev->rphy->identify.device_type != SAS_END_DEVICE);

	if (dev_is_sata(dev)) {
		ata_sas_slave_configure(scsi_dev, dev->sata_dev.ap);
		return 0;
	}

	sas_ha = dev->port->ha;

	sas_read_port_mode_page(scsi_dev);

	if (scsi_dev->tagged_supported) {
		scsi_change_queue_depth(scsi_dev, SAS_DEF_QD);
	} else {
		SAS_DPRINTK("device %llx, LUN %llx doesn't support "
			    "TCQ\n", SAS_ADDR(dev->sas_addr),
			    scsi_dev->lun);
		scsi_change_queue_depth(scsi_dev, 1);
	}

	scsi_dev->allow_restart = 1;

	return 0;
}

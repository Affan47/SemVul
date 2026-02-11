hpsa_add_device(struct ctlr_info *h, struct hpsa_scsi_dev_t *device)
{
	int rc = 0;

	if (!h->scsi_host)
		return 1;

	if (is_logical_device(device))
		rc = scsi_add_device(h->scsi_host, device->bus,
					device->target, device->lun);
	else
		rc = hpsa_add_sas_device(h->sas_host, device);

	return rc;
}

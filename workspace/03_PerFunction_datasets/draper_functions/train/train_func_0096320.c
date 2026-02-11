lpfc_aer_cleanup_state(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	int val, rc = -1;

	if (!isdigit(buf[0]))
		return -EINVAL;
	if (sscanf(buf, "%i", &val) != 1)
		return -EINVAL;
	if (val != 1)
		return -EINVAL;

	if (phba->hba_flag & HBA_AER_ENABLED)
		rc = pci_cleanup_aer_uncorrect_error_status(phba->pcidev);

	if (rc == 0)
		return strlen(buf);
	else
		return -EPERM;
}

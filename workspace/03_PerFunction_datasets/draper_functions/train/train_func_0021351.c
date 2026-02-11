lpfc_link_state_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;

	int status = -EINVAL;

	if ((strncmp(buf, "up", sizeof("up") - 1) == 0) &&
			(phba->link_state == LPFC_LINK_DOWN))
		status = phba->lpfc_hba_init_link(phba, MBX_NOWAIT);
	else if ((strncmp(buf, "down", sizeof("down") - 1) == 0) &&
			(phba->link_state >= LPFC_LINK_UP))
		status = phba->lpfc_hba_down_link(phba, MBX_NOWAIT);

	if (status == 0)
		return strlen(buf);
	else
		return status;
}

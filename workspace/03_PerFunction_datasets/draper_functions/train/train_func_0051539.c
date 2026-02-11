lpfc_oas_lun_state_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;
	int val = 0;

	if (!phba->cfg_fof)
		return -EPERM;

	if (!isdigit(buf[0]))
		return -EINVAL;

	if (sscanf(buf, "%i", &val) != 1)
		return -EINVAL;

	if ((val != 0) && (val != 1))
		return -EINVAL;

	phba->cfg_oas_lun_state = val;

	return strlen(buf);
}

sysfs_ctlreg_write(struct file *filp, struct kobject *kobj,
		   struct bin_attribute *bin_attr,
		   char *buf, loff_t off, size_t count)
{
	size_t buf_off;
	struct device *dev = container_of(kobj, struct device, kobj);
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;

	if (phba->sli_rev >= LPFC_SLI_REV4)
		return -EPERM;

	if ((off + count) > FF_REG_AREA_SIZE)
		return -ERANGE;

	if (count <= LPFC_REG_WRITE_KEY_SIZE)
		return 0;

	if (off % 4 || count % 4 || (unsigned long)buf % 4)
		return -EINVAL;


	if (memcmp(buf, LPFC_REG_WRITE_KEY, LPFC_REG_WRITE_KEY_SIZE))
		return -EINVAL;

	if (!(vport->fc_flag & FC_OFFLINE_MODE))
		return -EPERM;

	spin_lock_irq(&phba->hbalock);
	for (buf_off = 0; buf_off < count - LPFC_REG_WRITE_KEY_SIZE;
			buf_off += sizeof(uint32_t))
		writel(*((uint32_t *)(buf + buf_off + LPFC_REG_WRITE_KEY_SIZE)),
		       phba->ctrl_regs_memmap_p + off + buf_off);

	spin_unlock_irq(&phba->hbalock);

	return count;
}

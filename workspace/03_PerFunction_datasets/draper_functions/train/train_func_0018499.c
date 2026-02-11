pm8001_ctl_ob_queue_log_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	int offset;
	char *str = buf;
	int start = 0;
#define OB_MEMMAP(c)	\
		(*(u32 *)((u8 *)pm8001_ha->	\
		memoryMap.region[OB].virt_ptr +	\
		pm8001_ha->evtlog_ob_offset + (c)))

	for (offset = 0; offset < IB_OB_READ_TIMES; offset++) {
		str += sprintf(str, "0x%08x\n", OB_MEMMAP(start));
		start = start + 4;
	}
	pm8001_ha->evtlog_ob_offset += SYSFS_OFFSET;
	if (((pm8001_ha->evtlog_ob_offset) % (PM80XX_IB_OB_QUEUE_SIZE)) == 0)
		pm8001_ha->evtlog_ob_offset = 0;

	return str - buf;
}

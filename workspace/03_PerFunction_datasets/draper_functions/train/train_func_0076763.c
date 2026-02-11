pm8001_ctl_max_sg_list_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	if (pm8001_ha->chip_id == chip_8001) {
		return snprintf(buf, PAGE_SIZE, "%04d\n",
			pm8001_ha->main_cfg_tbl.pm8001_tbl.max_sgl & 0x0000FFFF
			);
	} else {
		return snprintf(buf, PAGE_SIZE, "%04d\n",
			pm8001_ha->main_cfg_tbl.pm80xx_tbl.max_sgl & 0x0000FFFF
			);
	}
}

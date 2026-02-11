qla2x00_allow_cna_fw_dump_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int val = 0;

	if (!IS_P3P_TYPE(vha->hw))
		return -EINVAL;

	if (sscanf(buf, "%d", &val) != 1)
		return -EINVAL;

	vha->hw->allow_cna_fw_dump = val != 0;

	return strlen(buf);
}

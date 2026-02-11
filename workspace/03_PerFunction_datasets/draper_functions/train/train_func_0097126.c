qla2x00_sysfs_read_fw_dump(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr,
			   char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	int rval = 0;

	if (!(ha->fw_dump_reading || ha->mctp_dump_reading))
		return 0;

	if (IS_P3P_TYPE(ha)) {
		if (off < ha->md_template_size) {
			rval = memory_read_from_buffer(buf, count,
			    &off, ha->md_tmplt_hdr, ha->md_template_size);
			return rval;
		}
		off -= ha->md_template_size;
		rval = memory_read_from_buffer(buf, count,
		    &off, ha->md_dump, ha->md_dump_size);
		return rval;
	} else if (ha->mctp_dumped && ha->mctp_dump_reading)
		return memory_read_from_buffer(buf, count, &off, ha->mctp_dump,
		    MCTP_DUMP_SIZE);
	else if (ha->fw_dump_reading)
		return memory_read_from_buffer(buf, count, &off, ha->fw_dump,
					ha->fw_dump_len);
	else
		return 0;
}

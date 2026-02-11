qla2x00_sysfs_read_vpd(struct file *filp, struct kobject *kobj,
		       struct bin_attribute *bin_attr,
		       char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;

	if (unlikely(pci_channel_offline(ha->pdev)))
		return -EAGAIN;

	if (!capable(CAP_SYS_ADMIN))
		return -EINVAL;

	if (IS_NOCACHE_VPD_TYPE(ha))
		ha->isp_ops->read_optrom(vha, ha->vpd, ha->flt_region_vpd << 2,
		    ha->vpd_size);
	return memory_read_from_buffer(buf, count, &off, ha->vpd, ha->vpd_size);
}

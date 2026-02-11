qlcnic_sysfs_read_esw_config(struct file *file,
					    struct kobject *kobj,
					    struct bin_attribute *attr,
					    char *buf, loff_t offset,
					    size_t size)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct qlcnic_adapter *adapter = dev_get_drvdata(dev);
	struct qlcnic_esw_func_cfg *esw_cfg;
	u8 pci_func;
	u32 count;
	int i;

	memset(buf, 0, size);
	esw_cfg = (struct qlcnic_esw_func_cfg *)buf;
	count = size / sizeof(struct qlcnic_esw_func_cfg);
	for (i = 0; i < adapter->ahw->total_nic_func; i++) {
		pci_func = adapter->npars[i].pci_func;
		if (pci_func >= count) {
			dev_dbg(dev, "%s: Total nic functions[%d], App sent function count[%d]\n",
				__func__, adapter->ahw->total_nic_func, count);
			continue;
		}
		if (!adapter->npars[i].eswitch_status)
			continue;

		esw_cfg[pci_func].pci_func = pci_func;
		if (qlcnic_get_eswitch_port_config(adapter, &esw_cfg[pci_func]))
			return -EINVAL;
	}
	qlcnic_swap32_buffer((u32 *)buf, size / sizeof(u32));
	return size;
}

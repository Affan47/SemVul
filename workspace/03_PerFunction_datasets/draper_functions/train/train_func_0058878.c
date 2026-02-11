add_error_device(struct aer_err_info *e_info, struct pci_dev *dev)
{
	if (e_info->error_dev_num < AER_MAX_MULTI_ERR_DEVICES) {
		e_info->dev[e_info->error_dev_num] = dev;
		e_info->error_dev_num++;
		return 0;
	}
	return -ENOSPC;
}

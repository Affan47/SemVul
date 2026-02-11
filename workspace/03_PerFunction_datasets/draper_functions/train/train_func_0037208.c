mei_txe_fw_status(struct mei_device *dev,
			     struct mei_fw_status *fw_status)
{
	const struct mei_fw_status *fw_src = &mei_txe_fw_sts;
	struct pci_dev *pdev = to_pci_dev(dev->dev);
	int ret;
	int i;

	if (!fw_status)
		return -EINVAL;

	fw_status->count = fw_src->count;
	for (i = 0; i < fw_src->count && i < MEI_FW_STATUS_MAX; i++) {
		ret = pci_read_config_dword(pdev,
			fw_src->status[i], &fw_status->status[i]);
		if (ret)
			return ret;
	}

	return 0;
}

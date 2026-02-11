netxen_request_firmware(struct netxen_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	int rc = 0;

	adapter->fw_type = NX_UNKNOWN_ROMIMAGE;

next:
	nx_get_next_fwtype(adapter);

	if (adapter->fw_type == NX_FLASH_ROMIMAGE) {
		adapter->fw = NULL;
	} else {
		rc = request_firmware(&adapter->fw,
				fw_name[adapter->fw_type], &pdev->dev);
		if (rc != 0)
			goto next;

		rc = netxen_validate_firmware(adapter);
		if (rc != 0) {
			release_firmware(adapter->fw);
			msleep(1);
			goto next;
		}
	}
}

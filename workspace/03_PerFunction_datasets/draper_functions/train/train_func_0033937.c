ipr_get_chip_info(const struct pci_device_id *dev_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ipr_chip); i++)
		if (ipr_chip[i].vendor == dev_id->vendor &&
		    ipr_chip[i].device == dev_id->device)
			return &ipr_chip[i];
	return NULL;
}

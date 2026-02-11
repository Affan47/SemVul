sis900_get_mac_addr(struct pci_device * pci_dev __unused, struct nic *nic)
{
	u16 signature;
	int i;


	signature = (u16) sis900_read_eeprom( EEPROMSignature);
	if (signature == 0xffff || signature == 0x0000) {
		printf ("sis900_probe: Error EERPOM read %hX\n", signature);
		return 0;
	}


	for (i = 0; i < 3; i++)
			((u16 *)(nic->node_addr))[i] = sis900_read_eeprom(i+EEPROMMACAddr);
	return 1;
}

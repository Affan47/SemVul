print_rev_avm(uint16_t hci_rev, uint16_t lmp_subver)
{
	if (lmp_subver == 0x01)
		printf("\tFirmware 03.%d.%d\n", hci_rev >> 8, hci_rev & 0xff);
	else
		printf("\tUnknown type\n");
}

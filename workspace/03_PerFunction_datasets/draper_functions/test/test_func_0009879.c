rtl8411b_is_qfn48(struct rtsx_pcr *pcr)
{
	u8 val = 0;

	rtsx_pci_read_register(pcr, RTL8411B_PACKAGE_MODE, &val);

	if (val & 0x2)
		return 1;
	else
		return 0;
}

rtl8411b_extra_init_hw(struct rtsx_pcr *pcr)
{
	rtsx_pci_init_cmd(pcr);

	if (rtl8411b_is_qfn48(pcr))
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				CARD_PULL_CTL3, 0xFF, 0xF5);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD30_DRIVE_SEL,
			0xFF, pcr->sd30_drive_sel_3v3);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CD_PAD_CTL,
			CD_DISABLE_MASK | CD_AUTO_DISABLE, CD_ENABLE);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, FUNC_FORCE_CTL,
			0x06, 0x00);

	return rtsx_pci_send_cmd(pcr, 100);
}

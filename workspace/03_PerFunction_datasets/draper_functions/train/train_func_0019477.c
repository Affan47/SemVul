rtsx_pci_init_hw(struct rtsx_pcr *pcr)
{
	int err;

	pcr->pcie_cap = pci_find_capability(pcr->pci, PCI_CAP_ID_EXP);
	rtsx_pci_writel(pcr, RTSX_HCBAR, pcr->host_cmds_addr);

	rtsx_pci_enable_bus_int(pcr);


	err = rtsx_pci_write_register(pcr, FPDCTL, SSC_POWER_DOWN, 0);
	if (err < 0)
		return err;


	udelay(200);

	rtsx_pci_disable_aspm(pcr);
	if (pcr->ops->optimize_phy) {
		err = pcr->ops->optimize_phy(pcr);
		if (err < 0)
			return err;
	}

	rtsx_pci_init_cmd(pcr);


	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_DIV, 0x07, 0x07);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, HOST_SLEEP_STATE, 0x03, 0x00);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_EN, 0x1E, 0);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CHANGE_LINK_STATE, 0x0A, 0);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DRIVE_SEL,
			0xFF, pcr->card_drive_sel);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL1,
			0xFF, SSC_8X_EN | SSC_SEL_4M);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL2, 0xFF, 0x12);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CHANGE_LINK_STATE, 0x16, 0x10);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, IRQSTAT0,
			LINK_RDY_INT, LINK_RDY_INT);


	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PERST_GLITCH_WIDTH, 0xFF, 0x80);


	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, RCCTL, 0x01, 0x00);


	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, NFTS_TX_CTRL, 0x02, 0);

	err = rtsx_pci_send_cmd(pcr, 100);
	if (err < 0)
		return err;


	rtsx_pci_write_config_byte(pcr, pcr->pcie_cap + PCI_EXP_LNKCTL + 1, 1);

	rtsx_pci_write_config_byte(pcr, 0x70F, 0x5B);

	if (pcr->ops->extra_init_hw) {
		err = pcr->ops->extra_init_hw(pcr);
		if (err < 0)
			return err;
	}


	if (pcr->ops->cd_deglitch)
		pcr->card_exist = pcr->ops->cd_deglitch(pcr);
	else
		pcr->card_exist = rtsx_pci_readl(pcr, RTSX_BIPR) & CARD_EXIST;

	return 0;
}

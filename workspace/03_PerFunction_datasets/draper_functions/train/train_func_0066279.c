cyz_issue_cmd(struct cyclades_card *cinfo,
		__u32 channel, __u8 cmd, __u32 param)
{
	struct BOARD_CTRL __iomem *board_ctrl = cinfo->board_ctrl;
	__u32 __iomem *pci_doorbell;
	unsigned int index;

	if (!cyz_is_loaded(cinfo))
		return -1;

	index = 0;
	pci_doorbell = &cinfo->ctl_addr.p9060->pci_doorbell;
	while ((readl(pci_doorbell) & 0xff) != 0) {
		if (index++ == 1000)
			return (int)(readl(pci_doorbell) & 0xff);
		udelay(50L);
	}
	cy_writel(&board_ctrl->hcmd_channel, channel);
	cy_writel(&board_ctrl->hcmd_param, param);
	cy_writel(pci_doorbell, (long)cmd);

	return 0;
}

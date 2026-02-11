lpfc_reset_barrier(struct lpfc_hba *phba)
{
	uint32_t __iomem *resp_buf;
	uint32_t __iomem *mbox_buf;
	volatile uint32_t mbox;
	uint32_t hc_copy, ha_copy, resp_data;
	int  i;
	uint8_t hdrtype;

	pci_read_config_byte(phba->pcidev, PCI_HEADER_TYPE, &hdrtype);
	if (hdrtype != 0x80 ||
	    (FC_JEDEC_ID(phba->vpd.rev.biuRev) != HELIOS_JEDEC_ID &&
	     FC_JEDEC_ID(phba->vpd.rev.biuRev) != THOR_JEDEC_ID))
		return;


	resp_buf = phba->MBslimaddr;


	if (lpfc_readl(phba->HCregaddr, &hc_copy))
		return;
	writel((hc_copy & ~HC_ERINT_ENA), phba->HCregaddr);
	readl(phba->HCregaddr);
	phba->link_flag |= LS_IGNORE_ERATT;

	if (lpfc_readl(phba->HAregaddr, &ha_copy))
		return;
	if (ha_copy & HA_ERATT) {

		writel(HA_ERATT, phba->HAregaddr);
		phba->pport->stopped = 1;
	}

	mbox = 0;
	((MAILBOX_t *)&mbox)->mbxCommand = MBX_KILL_BOARD;
	((MAILBOX_t *)&mbox)->mbxOwner = OWN_CHIP;

	writel(BARRIER_TEST_PATTERN, (resp_buf + 1));
	mbox_buf = phba->MBslimaddr;
	writel(mbox, mbox_buf);

	for (i = 0; i < 50; i++) {
		if (lpfc_readl((resp_buf + 1), &resp_data))
			return;
		if (resp_data != ~(BARRIER_TEST_PATTERN))
			mdelay(1);
		else
			break;
	}
	resp_data = 0;
	if (lpfc_readl((resp_buf + 1), &resp_data))
		return;
	if (resp_data  != ~(BARRIER_TEST_PATTERN)) {
		if (phba->sli.sli_flag & LPFC_SLI_ACTIVE ||
		    phba->pport->stopped)
			goto restore_hc;
		else
			goto clear_errat;
	}

	((MAILBOX_t *)&mbox)->mbxOwner = OWN_HOST;
	resp_data = 0;
	for (i = 0; i < 500; i++) {
		if (lpfc_readl(resp_buf, &resp_data))
			return;
		if (resp_data != mbox)
			mdelay(1);
		else
			break;
	}

clear_errat:

	while (++i < 500) {
		if (lpfc_readl(phba->HAregaddr, &ha_copy))
			return;
		if (!(ha_copy & HA_ERATT))
			mdelay(1);
		else
			break;
	}

	if (readl(phba->HAregaddr) & HA_ERATT) {
		writel(HA_ERATT, phba->HAregaddr);
		phba->pport->stopped = 1;
	}

restore_hc:
	phba->link_flag &= ~LS_IGNORE_ERATT;
	writel(hc_copy, phba->HCregaddr);
	readl(phba->HCregaddr);
}

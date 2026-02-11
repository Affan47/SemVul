rtsx_pci_card_exist(struct rtsx_pcr *pcr)
{
	unsigned int val;

	val = rtsx_pci_readl(pcr, RTSX_BIPR);
	if (pcr->ops->cd_deglitch)
		val = pcr->ops->cd_deglitch(pcr);

	return val;
}

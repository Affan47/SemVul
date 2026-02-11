il4965_hw_detect(struct il_priv *il)
{
	il->hw_rev = _il_rd(il, CSR_HW_REV);
	il->hw_wa_rev = _il_rd(il, CSR_HW_REV_WA_REG);
	il->rev_id = il->pci_dev->revision;
	D_INFO("HW Revision ID = 0x%X\n", il->rev_id);
}

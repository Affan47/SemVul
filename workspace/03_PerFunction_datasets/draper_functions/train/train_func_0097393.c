dmacheck (void)
{
	dmac_acr++;
	if (old_dmac && (dmac_cntr & CNTR_TCEN)) {
		if (dmac_wtc == 0)
			dmac_istr |= ISTR_E_INT;
		else
			dmac_wtc--;
	}
}

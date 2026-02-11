pmc_switch_pck_to_upllck(uint32_t ul_id, uint32_t ul_pres)
{
	uint32_t ul_timeout;

	PMC->PMC_PCK[ul_id] = PMC_PCK_CSS_UPLL_CLK | ul_pres;
	for (ul_timeout = PMC_TIMEOUT;
			!(PMC->PMC_SR & (PMC_SR_PCKRDY0 << ul_id));
			--ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}

	return 0;
}

pmc_switch_mainck_to_fastrc(uint32_t ul_moscrcf)
{
	uint32_t ul_needXTEN = 0;


	if (PMC->CKGR_MOR & CKGR_MOR_MOSCXTEN) {
		PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCRCF_Msk) |
				PMC_CKGR_MOR_KEY_VALUE | CKGR_MOR_MOSCRCEN |
				ul_moscrcf;
	} else {
		ul_needXTEN = 1;
		PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCRCF_Msk) |
				PMC_CKGR_MOR_KEY_VALUE | CKGR_MOR_MOSCRCEN |
				CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCXTST_Msk |
				ul_moscrcf;
	}


	while (!(PMC->PMC_SR & PMC_SR_MOSCRCS));


	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCSEL) | PMC_CKGR_MOR_KEY_VALUE;


	if (ul_needXTEN) {
		PMC->CKGR_MOR = (PMC->CKGR_MOR & ~CKGR_MOR_MOSCXTEN) |
				PMC_CKGR_MOR_KEY_VALUE;
	}
}

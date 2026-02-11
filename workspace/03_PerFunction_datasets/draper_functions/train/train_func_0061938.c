pmc_enable_waitmode(void)
{
	uint32_t i;

	PMC->PMC_FSMR |= PMC_FSMR_LPM;
	SCB->SCR &= (uint32_t) ~ SCB_SCR_SLEEPDEEP_Msk;
	__WFE();


	for (i = 0; i < 500; i++) {
		__NOP();
	}
	while (!(PMC->CKGR_MOR & CKGR_MOR_MOSCRCEN));
}

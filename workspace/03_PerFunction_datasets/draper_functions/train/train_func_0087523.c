pxa168_init_hw(struct pxa168_eth_private *pep)
{
	int err = 0;


	wrl(pep, INT_MASK, 0);
	wrl(pep, INT_CAUSE, 0);

	wrl(pep, INT_W_CLEAR, 0);


	abort_dma(pep);

	err = init_hash_table(pep);
	if (err)
		return err;

	wrl(pep, SDMA_CONFIG, SDCR_BSZ8 |
	    SDCR_RIFB |
	    SDCR_BLMT |
	    SDCR_BLMR |
	    SDCR_RC_MAX_RETRANS);

	wrl(pep, PORT_CONFIG, PCR_HS);
	set_port_config_ext(pep);

	return err;
}

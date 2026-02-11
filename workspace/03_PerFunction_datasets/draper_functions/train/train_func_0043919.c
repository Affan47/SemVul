card_start(struct s_smc *smc)
{
	int i ;
#ifdef	PCI
	u_char	rev_id ;
	u_short word;
#endif

	smt_stop_watchdog(smc) ;

#ifdef	PCI


	outpw(FM_A(FM_MDREG1),FM_MINIT) ;
	outp(ADDR(B0_CTRL), CTRL_HPI_SET) ;
	hwt_wait_time(smc,hwt_quick_read(smc),MS2BCLK(10)) ;


	outp(ADDR(B0_CTRL),CTRL_RST_SET) ;
	i = (int) inp(ADDR(B0_CTRL)) ;
	SK_UNUSED(i) ;
	outp(ADDR(B0_CTRL), CTRL_RST_CLR) ;


	outp(ADDR(B0_TST_CTRL), TST_CFG_WRITE_ON) ;
	word = inpw(PCI_C(PCI_STATUS)) ;
	outpw(PCI_C(PCI_STATUS), word | PCI_ERRBITS) ;
	outp(ADDR(B0_TST_CTRL), TST_CFG_WRITE_OFF) ;


	outp(ADDR(B0_CTRL), CTRL_MRST_CLR|CTRL_HPI_CLR) ;


	rev_id = inp(PCI_C(PCI_REV_ID)) ;
	if ((rev_id & 0xf0) == SK_ML_ID_1 || (rev_id & 0xf0) == SK_ML_ID_2) {
		smc->hw.hw_is_64bit = TRUE ;
	} else {
		smc->hw.hw_is_64bit = FALSE ;
	}


	if (!smc->hw.hw_is_64bit) {
		outpd(ADDR(B4_R1_F), RX_WATERMARK) ;
		outpd(ADDR(B5_XA_F), TX_WATERMARK) ;
		outpd(ADDR(B5_XS_F), TX_WATERMARK) ;
	}

	outp(ADDR(B0_CTRL),CTRL_RST_CLR) ;
	outp(ADDR(B0_LED),LED_GA_OFF|LED_MY_ON|LED_GB_OFF) ;


	outpd(ADDR(B2_WDOG_INI),0x6FC23AC0) ;


	smc->hw.is_imask = ISR_MASK ;
	smc->hw.hw_state = STOPPED ;
#endif
	GET_PAGE(0) ;
}

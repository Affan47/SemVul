mac_drv_repair_descr(struct s_smc *smc)
{
	u_long	phys ;

	if (smc->hw.hw_state != STOPPED) {
		SK_BREAK() ;
		SMT_PANIC(smc,HWM_E0013,HWM_E0013_MSG) ;
		return ;
	}


	phys = repair_txd_ring(smc,smc->hw.fp.tx[QUEUE_A0]) ;
	outpd(ADDR(B5_XA_DA),phys) ;
	if (smc->hw.fp.tx_q[QUEUE_A0].tx_used) {
		outpd(ADDR(B0_XA_CSR),CSR_START) ;
	}
	phys = repair_txd_ring(smc,smc->hw.fp.tx[QUEUE_S]) ;
	outpd(ADDR(B5_XS_DA),phys) ;
	if (smc->hw.fp.tx_q[QUEUE_S].tx_used) {
		outpd(ADDR(B0_XS_CSR),CSR_START) ;
	}


	phys = repair_rxd_ring(smc,smc->hw.fp.rx[QUEUE_R1]) ;
	outpd(ADDR(B4_R1_DA),phys) ;
	outpd(ADDR(B0_R1_CSR),CSR_START) ;
}
